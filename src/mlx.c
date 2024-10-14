/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:33:03 by kipouliq          #+#    #+#             */
/*   Updated: 2024/10/14 18:19:09 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	quit_cube(void *param)
{
	(void)param;
	printf("quitting\n");
	exit(0);
	return (0);
}

t_mlx_img	*init_img(t_window_mlx *data)
{
	t_mlx_img	*img;

	img = malloc(sizeof(t_mlx_img));
	if (!img)
		return (error_exit(NULL), NULL);
	img->img_ptr = mlx_new_image(data->mlx_ptr, data->width, data->height);
	if (!img->img_ptr)
		return (NULL);
	img->img_addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len,
			&img->endian);
	return (img);
}

void	img_pix_put(t_mlx_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->img_addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	draw_x_line(t_mlx_img *img, int x_pos, int y_pos, int color)
{
	int	x_max;

	x_max = x_pos + ONE_UNIT;
	while (x_pos < x_max)
	{
		img_pix_put(img, x_pos, y_pos, color);
		x_pos++;
	}
	return (0);
}

int fill_x_line(t_mlx_img *img, int x_pos, int y_pos, int color)
{
    int x_max;

    x_max = x_pos + ONE_UNIT;
    while (++x_pos < x_max)
        img_pix_put(img, x_pos, y_pos, color);
    return (0);
}

int	draw_y_line(t_mlx_img *img, int x_pos, int y_pos_init, char terrain)
{
	int	y_pos;
	int	y_max;

    (void) terrain;     
	y_pos = y_pos_init;
	y_max = y_pos + ONE_UNIT;
	while (y_pos < y_max)
	{
		img_pix_put(img, x_pos, y_pos, 0x808080);
        if (terrain == '1')
            draw_x_line(img, x_pos + 1, y_pos, 0xFFFFFF);
		y_pos += 1;
	}
	return (0);
}

int	draw_map(t_mlx_img *img, char **map)
{
	int	i;
	int	j;
	int	px_x_pos;
	int	px_y_pos;

	i = -1;
	px_y_pos = 10;
	while (map[++i])
	{
		j = -1;
		px_x_pos = 10;
		while (map[i][++j])
		{
			if (!ft_is_space(map[i][j]))
			{
				draw_y_line(img, px_x_pos, px_y_pos, map[i][j]);
				draw_x_line(img, px_x_pos, px_y_pos, 0x808080);
                px_x_pos += ONE_UNIT;
			}
		}
		draw_y_line(img, px_x_pos, px_y_pos, map[i][j]);
		px_y_pos += ONE_UNIT;
	}
	i = 0;
	px_x_pos = 10;
	while (i < (int)ft_strlen(map[get_arr_size(map) - 1]))
    {
		draw_x_line(img, px_x_pos, px_y_pos, 0x808080);
        px_x_pos += ONE_UNIT;
        i++;
    }
	return (0);
}

int	start_raycasting(t_window_mlx *data, char **map)
{
	t_mlx_img	*img;

	img = init_img(data);
	if (!img)
		return (error_exit(NULL), -1);
	draw_map(img, map);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img->img_ptr, 0, 0);
	return (0);
}

int	start_mlx(int height, int width, char **map)
{
	t_window_mlx	data;

	data.mlx_ptr = mlx_init();
	data.width = width;
	data.height = height;
	if (!data.mlx_ptr)
		return (-1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, width, height, "cube3D");
	if (!data.win_ptr)
		return (-1);
	start_raycasting(&data, map);
	mlx_key_hook(data.win_ptr, handle_keyboard_inputs, NULL);
	mlx_loop(data.mlx_ptr);
	return (0);
}
