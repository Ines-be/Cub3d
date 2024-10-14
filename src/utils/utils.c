/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:04:59 by kipouliq          #+#    #+#             */
/*   Updated: 2024/10/14 17:56:01 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	error_exit(char *str)
{
	printf("Error\n");
	if (str)
		printf("%s\n", str);
	exit(-1);
	return (-1);
}

int	get_arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_arr_until_idx(char **arr, int idx)
{
	int	i;

	i = -1;
	while (arr[++i] && i < idx)
		free(arr[i]);
}
