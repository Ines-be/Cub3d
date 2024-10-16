/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:34:53 by inbennou          #+#    #+#             */
/*   Updated: 2024/10/16 17:07:10 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_list	*start;
	t_cub	cub;

	parsing(ac, av, &start, &cub);
	free_list(start); // a la fin du parsing
	free_cub(&cub); // a la fin du prog
}
