/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:12:59 by inbennou          #+#    #+#             */
/*   Updated: 2024/10/14 17:20:03 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// si on a autre chose qu'un \n a la fin de la ligne ca marche pas :/
int	get_int(char **split_elem, t_list *start, t_cub *cub, char *color)
{
	char	*temp;
	int		ret;

	temp = NULL;
	temp = ft_strtrim(color, "\n");
	ret = pos_atoi(temp);
	if (ret < 0)
	{
		ft_free(color);
		ft_free(temp);
		texture_error(split_elem, start, cub,
			"Format error. exemple: C 225, 30, 0");
	}
	ft_free(temp);
	return (ret);
}

void	get_color(char **tab, t_list *start, t_cub *cub, char id)
{
	char	*color;
	int		red;
	int		green;
	int		blue;
	int		i;

	color = NULL;
	i = 0;
	if (!tab || size_tab(tab) != 4)
		texture_error(tab, start, cub, "Format error. exemple: C 225, 30, 0");
	while (tab[++i])
	{
		color = ft_strtrim(tab[i], ",");
		if (i == 1)
			red = get_int(tab, start, cub, color);
		if (i == 2)
			green = get_int(tab, start, cub, color);
		if (i == 3)
			blue = get_int(tab, start, cub, color);
		ft_free(color);
	}
	if (id == 'C' && cub->c_color < 0)
		cub->c_color = create_rgb(red, green, blue);
	if (id == 'F' && cub->f_color < 0)
		cub->f_color = create_rgb(red, green, blue);
}
