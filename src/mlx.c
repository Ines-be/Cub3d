/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:33:03 by kipouliq          #+#    #+#             */
/*   Updated: 2024/10/22 18:34:05 by kipouliq         ###   ########.fr       */
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
				cub->player.pos.x = j + 0.5;
				cub->player.pos.y = get_arr_size(cub->map) - i - 0.5;
				printf("player x = %f\n", cub->player.pos.x);
				printf("player y = %f\n", cub->player.pos.y);
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

	player_pos.x = ONE_UNIT * x + 10;
	player_pos.y = ONE_UNIT * (arr_size - y) + 10;
	return (player_pos);
}

t_position	get_pos_from_vector(t_position init_pos, t_vector vector)
{
	t_position	new_pos;

	new_pos.x = init_pos.x + vector.x;
	new_pos.y = init_pos.y + vector.y;
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
	printf("draw player pos = %f %f\n", cub->player.pos.x, cub->player.pos.y);
	draw(img, coordinates_to_px(cub->player.pos.x, cub->player.pos.y,
			arr_size));
	printf("draw player pos = %f %f\n", cub->player.pos.x, cub->player.pos.y);
	draw(img, coordinates_to_px(fov_l.x, fov_l.y, arr_size));
	draw(img, coordinates_to_px(fov_r.x, fov_r.y, arr_size));
	draw(img, coordinates_to_px(dir.x, dir.y, arr_size));
	return (0);
}

int	draw_ray(t_mlx_img *img, t_position start, t_position end, int arr_size)
{
	t_position	px_start;
	t_position	px_end;
	int			x_term;
	int			y_term;
	int			error_term;

	px_start = coordinates_to_px(start.x, start.y, arr_size);
	px_end = coordinates_to_px(end.x, end.y, arr_size);
	x_term = px_end.x - px_start.x;
	y_term = px_end.y - px_start.y;
	error_term = 2 * y_term - x_term;
	printf(" %f %f %f %f %d %d %d\n", px_start.x, px_start.y, px_end.x,
		px_end.y, x_term, y_term, error_term);
    while (px_start.x != px_end.x && px_start.y != px_end.y)
    {
        img_pix_put(img, px_start.x, px_start.y, 0x008000);
        if (px_start.x > px_end.x)
            px_start.x++;
        else
            px_start.x--;
        if (error_term > 0)
        {
            px_start.y++;
            error_term = error_term + (2 * y_term) - (2 * x_term);
        }
        else
            error_term = error_term * (2 * y_term);
    }
	return (0);
}

int	init_camera_vectors(t_cub *cub)
{
	cub->player.dir.x = 0;
	cub->player.dir.y = 0.5;
	cub->player.fov_l.x = -0.5;
	cub->player.fov_l.y = 0.5;
	cub->player.fov_r.x = 0.5;
	cub->player.fov_r.y = 0.5;
	return (0);
}

int	start_raycasting(t_window_mlx *data, t_cub *cub)
{
	t_mlx_img	*img;

	img = init_img(data);
	if (!img)
		return (error_exit(NULL), -1);
	find_player_init_pos(cub);
	printf("player init position = %f %f\n", cub->player.pos.x,
		cub->player.pos.y);
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
	t_position	end;

	img = init_img(&cub->mlx_data);
	if (!img)
		return (error_exit(NULL), -1);
	draw_map(img, cub->map);
	draw_player(img, cub);
	end.x = cub->player.pos.x - 1;
	end.y = cub->player.pos.y - 1;
	printf("player pos = x %f y %f\n", cub->player.pos.x, cub->player.pos.y);
	printf("cam l = %f %f\n", cub->player.fov_l.x, cub->player.fov_l.y);
	draw_ray(img, cub->player.pos, end, get_arr_size(cub->map));
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
