/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:34:53 by inbennou          #+#    #+#             */
/*   Updated: 2024/10/14 17:14:57 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_list	*start;
	t_cub	cub;

	parsing(ac, av, &start, &cub);
	printf("c-color = %d et f_color = %d\n", cub.c_color, cub.f_color);
	free_cub(&cub);
	free_list(start);
}
