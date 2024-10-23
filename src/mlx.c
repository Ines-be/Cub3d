/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:33:03 by kipouliq          #+#    #+#             */
/*   Updated: 2024/10/23 17:43:30 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	quit_cube(t_cub *cub)
{
	(void)cub;
	printf("quitting\n");
	exit(0);
	return (0);
}

void	find_player_init_pos(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (is_player_direction(cub->map[i][j]))
			{
				cub->player.pos.x = j * 10 + 5;
				cub->player.pos.y = i * 10 + 5;
				return ;
			}
		}
	}
}

void	draw(t_mlx_img *img, t_position pos)
{
	int	i;

	i = 1;
	while (i <= 4)
	{
		img_pix_put(img, pos.x, pos.y - i, 0xFF0000);
		i++;
	}
	i = 1;
	while (i <= 2)
	{
		img_pix_put(img, pos.x - i, pos.y, 0xFF0000);
		i++;
	}
	i = 1;
	while (i <= 2)
	{
		img_pix_put(img, pos.x + i, pos.y, 0xFF0000);
		i++;
	}
}

t_position	coordinates_to_px(double x, double y, int arr_size)
{
	t_position	player_pos;

    (void) arr_size;
    
    x /= 10;
    y /= 10;
	player_pos.x = (ONE_UNIT * x + 10);
	player_pos.y = (ONE_UNIT * y + 10);
	return (player_pos);
}

t_position	get_pos_from_vector(t_position init_pos, t_vector vector)
{
	t_position	new_pos;

	new_pos.x = init_pos.x - vector.x;
	new_pos.y = init_pos.y - vector.y;
	return (new_pos);
}

t_vector	rotate_vector(t_vector vec, double angle)
{
	t_vector	new_vector;
	double		sin_angle;
	double		cos_angle;

	sin_angle = sin(angle);
	cos_angle = cos(angle);
	new_vector.x = vec.x * cos_angle - vec.y * sin_angle;
	new_vector.y = vec.x * sin_angle + vec.y * cos_angle;
	return (new_vector);
}

int	draw_player(t_mlx_img *img, t_cub *cub)
{
	t_position	fov_l;
	t_position	fov_r;
	t_position	dir;
	int			arr_size;

	arr_size = get_arr_size(cub->map);
	fov_l = get_pos_from_vector(cub->player.pos, cub->player.fov_l);
	fov_r = get_pos_from_vector(cub->player.pos, cub->player.fov_r);
	dir = get_pos_from_vector(cub->player.pos, cub->player.dir);
	draw(img, coordinates_to_px(cub->player.pos.x, cub->player.pos.y,
			arr_size));
	draw(img, coordinates_to_px(fov_l.x, fov_l.y, arr_size));
	draw(img, coordinates_to_px(fov_r.x, fov_r.y, arr_size));
	draw(img, coordinates_to_px(dir.x, dir.y, arr_size));
	return (0);
}

void	ft_swap(double *a, double *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	draw_ray_horizontal(t_mlx_img *img, t_position start, t_position end, int arr_size)
{
	t_position	px_start;
	t_position	px_end;
	int			delta_x;
	int			delta_y;
	int			decision_term;
	int			dir;
	int			y;
	int			i;

	px_start = coordinates_to_px(start.x, start.y, arr_size);
	px_end = coordinates_to_px(end.x, end.y, arr_size);
	if (px_start.x > px_end.x)
	{
		ft_swap(&px_start.x, &px_end.x);
		ft_swap(&px_start.y, &px_end.y);
	}
	delta_x = px_end.x - px_start.x;
	delta_y = px_end.y - px_start.y;
	if (delta_y > 0)
		dir = 1;
	else
		dir = -1;
	delta_y *= dir;
	i = 0;
	y = px_start.y;
	decision_term = 2 * delta_y - delta_x;
	while (i < delta_x + 1)
	{
		img_pix_put(img, px_start.x + i, y, 0x008000);
		if (decision_term >= 0)
		{
			y += dir;
			decision_term -= 2 * delta_x;
		}
		else
			decision_term += 2 * delta_y;
        i++;
	}
	// need to check if dx is negativee ?
	return (0);
}

int	draw_ray_vertical(t_mlx_img *img, t_position start, t_position end, int arr_size)
{
	t_position	px_start;
	t_position	px_end;
	int			delta_x;
	int			delta_y;
	int			decision_term;
	int			dir;
	int			x;
	int			i;

	px_start = coordinates_to_px(start.x, start.y, arr_size);
	px_end = coordinates_to_px(end.x, end.y, arr_size);
	if (px_start.y > px_end.y)
	{
		ft_swap(&px_start.x, &px_end.x);
		ft_swap(&px_start.y, &px_end.y);
	}
	delta_x = px_end.x - px_start.x;
	delta_y = px_end.y - px_start.y;
	if (delta_x > 0)
		dir = 1;
	else
		dir = -1;
	delta_x *= dir;
	i = 0;
	x = px_start.x;
	decision_term = 2 * delta_x - delta_y;
	while (i < delta_y + 1)
	{
		img_pix_put(img, x, px_start.y + i, 0x008000);
		if (decision_term >= 0)
		{
			x += dir;
			decision_term -= 2 * delta_y;
		}
		else
			decision_term += 2 * delta_x;
        i++;
	}
	// need to check if dx is negativee ?
	return (0);
}

int draw_ray(t_mlx_img *img, t_position start, t_position end, int arr_size)
{
    if (abs((int)end.x > (int)start.x) > abs((int)end.y - (int)start.y))
        draw_ray_horizontal(img, start, end, arr_size);
    else
        draw_ray_vertical(img, start, end, arr_size);
    return (0);
}

int	init_camera_vectors(t_cub *cub)
{
	cub->player.dir.x = 0;
	cub->player.dir.y = 20;
	cub->player.fov_l.x = -5;
	cub->player.fov_l.y = 20;
	cub->player.fov_r.x = 5;
	cub->player.fov_r.y = 20;
	return (0);
}

int shoot_rays(t_cub *cub)
{
    t_vector *rays;
    t_position fov_l;
    t_position fov_r;

    rays = malloc(sizeof(t_vector) * 10);
    if (!rays)
        return (error_exit(NULL));
    fov_l = get_pos_from_vector(cub->player.pos, cub->player.fov_l);
    fov_r = get_pos_from_vector(cub->player.pos, cub->player.fov_r);
    return (0);
}

int	start_raycasting(t_window_mlx *data, t_cub *cub)
{
	t_mlx_img	*img;

	img = init_img(data);
	if (!img)
		return (error_exit(NULL), -1);
	find_player_init_pos(cub);
	draw_map(img, cub->map);
	init_camera_vectors(cub);
	draw_player(img, cub);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img->img_ptr, 0, 0);
	mlx_destroy_image(data->mlx_ptr, img->img_ptr);
	return (0);
}

int	refresh_raycasting(t_cub *cub)
{
	t_mlx_img	*img;

	img = init_img(&cub->mlx_data);
	if (!img)
		return (error_exit(NULL), -1);
	draw_map(img, cub->map);
	draw_player(img, cub);
	draw_ray(img, cub->player.pos, get_pos_from_vector(cub->player.pos, cub->player.fov_l), get_arr_size(cub->map));
	draw_ray(img, cub->player.pos, get_pos_from_vector(cub->player.pos, cub->player.fov_r), get_arr_size(cub->map));
	draw_ray(img, cub->player.pos, get_pos_from_vector(cub->player.pos, cub->player.dir), get_arr_size(cub->map));
	mlx_put_image_to_window(cub->mlx_data.mlx_ptr, cub->mlx_data.win_ptr,
		img->img_ptr, 0, 0);
	mlx_destroy_image(cub->mlx_data.mlx_ptr, img->img_ptr);
	return (0);
}

int	start_mlx(int height, int width, t_cub *cub)
{
	cub->mlx_data.mlx_ptr = mlx_init();
	cub->mlx_data.width = width;
	cub->mlx_data.height = height;
	if (!cub->mlx_data.mlx_ptr)
		return (-1);
	cub->mlx_data.win_ptr = mlx_new_window(cub->mlx_data.mlx_ptr, width, height,
			"cub3D");
	if (!cub->mlx_data.win_ptr)
		return (-1);
	start_raycasting(&cub->mlx_data, cub);
	// mlx_key_hook(cub->mlx_data.win_ptr, handle_keyboard_inputs, cub);
	mlx_hook(cub->mlx_data.win_ptr, 2, (1L << 0), handle_keyboard_inputs, cub);
	mlx_loop(cub->mlx_data.mlx_ptr);
	return (0);
}
