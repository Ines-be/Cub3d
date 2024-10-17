/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:33:03 by kipouliq          #+#    #+#             */
/*   Updated: 2024/10/17 17:27:52 by kipouliq         ###   ########.fr       */
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
				cub->player_pos.x = j;
				cub->player_pos.y = i;
				printf("i = %d\n", i);
				printf("j = %d\n", j);
				return ;
			}
		}
	}
}

void	draw_player(t_mlx_img *img, t_cub *cub)
{
	int	i;

	i = 1;
	while (i <= 4)
	{
		img_pix_put(img, cub->player_pos.x, cub->player_pos.y - i, 0xFF0000);
		i++;
	}
	i = 1;
	while (i <= 2)
	{
		img_pix_put(img, cub->player_pos.x - i, cub->player_pos.y, 0xFF0000);
		i++;
	}
	i = 1;
	while (i <= 2)
	{
		img_pix_put(img, cub->player_pos.x + i, cub->player_pos.y, 0xFF0000);
		i++;
	}
}

int	init_player(t_mlx_img *img, t_cub *cub)
{
	cub->player_pos.x = (ONE_UNIT * cub->player_pos.x) + (ONE_UNIT / 2) + 10;
	cub->player_pos.y = (ONE_UNIT * cub->player_pos.y) + (ONE_UNIT / 2) + 10;
	printf("x = %f\n", cub->player_pos.x);
	printf("y = %f\n", cub->player_pos.y);
	draw_player(img, cub);
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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img->img_ptr, 0, 0);
	return (0);
}

int	refresh_raycasting(t_window_mlx *data, t_cub *cub)
{
	t_mlx_img	*img;

	img = init_img(&cub->mlx_data);
	if (!img)
		return (error_exit(NULL), -1);
	draw_map(img, cub->map);
	draw_player(img, cub);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img->img_ptr, 0, 0);
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
