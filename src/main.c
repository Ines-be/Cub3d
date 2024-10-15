/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:34:53 by inbennou          #+#    #+#             */
/*   Updated: 2024/10/15 15:59:07 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	parsing(ac, av, &cub);
	printf("c-color = %d et f_color = %d\n", cub.c_color, cub.f_color);
	printf("cub %s %s %s %s %d %d\n", cub.no_text, cub.so_text, cub.ea_text,
		cub.we_text, cub.c_color, cub.f_color);
	free_cub(&cub);
}
