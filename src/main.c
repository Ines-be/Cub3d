/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:34:53 by inbennou          #+#    #+#             */
/*   Updated: 2024/10/16 19:02:19 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_list	*start;
	t_list	*file;
	t_cub	cub;

	parsing(ac, av, &start, &cub);
	file = start;
	skip_elements(&start);
	printf("%s\n", start->content);
	free_list(file); // a la fin du parsing
	free_cub(&cub); // a la fin du prog
}
