/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:30:14 by inbennou          #+#    #+#             */
/*   Updated: 2024/10/14 16:05:01 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	map_error(int fd, char *msg, t_list *file_content)
{
	printf("Error\n%s\n", msg);
	if (fd > 0)
		close(fd);
	if (file_content)
		free_list(file_content);
	exit(EXIT_FAILURE);
}

void	texture_error(char **tab, t_list *start, t_cub *cub, char *msg)
{
	if (tab)
		free_tab(tab);
	free_cub(cub);
	map_error(-1, msg, start);
}
