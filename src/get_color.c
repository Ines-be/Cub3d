/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:12:59 by inbennou          #+#    #+#             */
/*   Updated: 2024/10/16 18:38:55 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_color(char **tab, t_list *start, t_cub *cub, char id)
{
	char	*color;
	char	**rgb;
	int		red;
	int		green;
	int		blue;

	color = NULL;
	rgb = NULL;
	if (!tab || size_tab(tab) != 2)
		texture_error(tab, start, cub, "Format error. exemple: C 225,30,0");
	color = ft_strtrim(tab[1], "\n");
	rgb = ft_split(color, ',');
	if (!rgb)
		color_error(tab, start, cub, color);
	red = pos_atoi(rgb[0]);
	green = pos_atoi(rgb[1]);
	blue = pos_atoi(rgb[2]);
	ft_free(color);
	free_tab(rgb);
	if (red < 0 || green < 0 || blue < 0)
		texture_error(tab, start, cub, "Format error. exemple: C 225,30,0");
	if (id == 'C' && cub->c_color < 0)
		cub->c_color = create_rgb(red, green, blue);
	if (id == 'F' && cub->f_color < 0)
		cub->f_color = create_rgb(red, green, blue);
}
