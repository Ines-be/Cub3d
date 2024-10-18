/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:33:03 by kipouliq          #+#    #+#             */
/*   Updated: 2024/10/18 18:24:02 by kipouliq         ###   ########.fr       */
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
				cub->player.pos.x = j;
				cub->player.pos.y = i;
				printf("i = %d\n", i);
				printf("j = %d\n", j);
				return ;
			}
		}
	}
}

void	draw(t_mlx_img *img, t_vector *pos)
{
	int	i;

	i = 1;
	while (i <= 4)
	{
		img_pix_put(img, pos->x, pos->y - i, 0xFF0000);
		i++;
	}
	i = 1;
	while (i <= 2)
	{
		img_pix_put(img, pos->x - i, pos->y, 0xFF0000);
		i++;
	}
	i = 1;
	while (i <= 2)
	{
		img_pix_put(img, pos->x + i, pos->y, 0xFF0000);
		i++;
	}
}

int	init_player(t_mlx_img *img, t_cub *cub)
{
	cub->player.pos.x = (ONE_UNIT * cub->player.pos.x) + (ONE_UNIT / 2) + 10;
	cub->player.pos.y = (ONE_UNIT * cub->player.pos.y) + (ONE_UNIT / 2) + 10;
	printf("x = %f\n", cub->player.pos.x);
	printf("y = %f\n", cub->player.pos.y);
	draw(img, &cub->player.pos);
	return (0);
}

t_vector	rotate_vector(t_vector vector, double angle)
{
	t_vector	new_vector;
	double		sin_angle;
	double		cos_angle;

	sin_angle = sin(angle);
	cos_angle = cos(angle);
	new_vector.x = vector.x * cos_angle - vector.y * sin_angle;
	new_vector.y = vector.x * sin_angle + vector.y * cos_angle;
	return (new_vector);
}

// int init_camera(t_mlx_img *img, t_cub *cub)
// {
//     t_vector vec_dir;
//     t_vector vec_cam_plane_r;
//     t_vector vec_cam_plane_l;

//     vec_dir.y = cub->player_pos.y - (ONE_UNIT / 2);
//     vec_dir.x = cub->player_pos.x;
//     vec_cam_plane_r.x = vec_dir.x + (ONE_UNIT / 2);
//     vec_cam_plane_r.y = vec_dir.y;
//     vec_cam_plane_l.x = vec_dir.x - (ONE_UNIT / 2);
//     vec_cam_plane_l.y = vec_dir.y;
//     draw(img, &vec_dir);
//     draw(img, &vec_cam_plane_l);
//     draw(img, &vec_cam_plane_r);
//     return (0);
// }

int	draw_player(t_mlx_img *img, t_cub *cub)
{
	draw(img, &cub->player.dir);
	draw(img, &cub->player.pos);
	draw(img, &cub->player.fov_l);
	draw(img, &cub->player.fov_r);
	return (0);
}

int	init_camera(t_mlx_img *img, t_cub *cub)
{
	cub->player.dir.y = cub->player.pos.y - (ONE_UNIT / 2);
	cub->player.dir.x = cub->player.pos.x;
	cub->player.fov_l.x = cub->player.dir.x - (ONE_UNIT / 2);
	cub->player.fov_l.y = cub->player.dir.y;
	cub->player.fov_r.x = cub->player.dir.x + (ONE_UNIT / 2);
	cub->player.fov_r.y = cub->player.dir.y;
	draw(img, &cub->player.dir);
	draw(img, &cub->player.fov_l);
	draw(img, &cub->player.fov_r);
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
	init_player(img, cub);
	init_camera(img, cub);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img->img_ptr, 0, 0);
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
	mlx_put_image_to_window(cub->mlx_data.mlx_ptr, cub->mlx_data.win_ptr,
		img->img_ptr, 0, 0);
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
			"cube3D");
	if (!cub->mlx_data.win_ptr)
		return (-1);
	start_raycasting(&cub->mlx_data, cub);
	// mlx_key_hook(cub->mlx_data.win_ptr, handle_keyboard_inputs, cub);
	mlx_hook(cub->mlx_data.win_ptr, 2, (1L << 0), handle_keyboard_inputs, cub);
	mlx_loop(cub->mlx_data.mlx_ptr);
	return (0);
}
