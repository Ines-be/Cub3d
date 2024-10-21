/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:33:03 by kipouliq          #+#    #+#             */
/*   Updated: 2024/10/21 18:28:02 by kipouliq         ###   ########.fr       */
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
				cub->player.pos.y = i + 0.5;
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

t_position	coordinates_to_px(double x, double y)
{
	t_position	player_pos;

	player_pos.x = ONE_UNIT * x + 10;
	player_pos.y = ONE_UNIT * y + 10;
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

	fov_l = get_pos_from_vector(cub->player.pos, cub->player.fov_l);
	fov_r = get_pos_from_vector(cub->player.pos, cub->player.fov_r);
	dir = get_pos_from_vector(cub->player.pos, cub->player.dir);
	draw(img, coordinates_to_px(cub->player.pos.x, cub->player.pos.y));
	draw(img, coordinates_to_px(fov_l.x, fov_l.y));
	draw(img, coordinates_to_px(fov_r.x, fov_r.y));
	draw(img, coordinates_to_px(dir.x, dir.y));
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
	printf("player pos = x %f y %f\n", cub->player.pos.x, cub->player.pos.y);
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
