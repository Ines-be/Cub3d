/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:20:05 by kipouliq          #+#    #+#             */
/*   Updated: 2024/10/14 17:47:16 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	**get_map(t_list **file)
{
	char	**map;
	int		i;
	t_list	*current;

	map = malloc(sizeof(char *) * (ft_lstsize(*file) + 1));
	if (!map)
		return (error_exit(NULL), NULL);
	i = 0;
	current = *file;
	while (current)
	{
		map[i] = ft_strtrim(current->content, "\n");
		if (!map[i])
			return (free_arr_until_idx(map, i), error_exit(NULL), NULL);
		current = current->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

int	check_sides_null(char **map, int i, int j)
{
	if (!map[i][j - 1] || !map[i][j + 1])
		return (1);
	if (j > (int)ft_strlen(map[i - 1]) || j > (int)ft_strlen(map[i + 1]))
		return (1);
	return (0);
}

int	is_border(char **map, int i, int j)
{
	if (is_map_char(map[i][j]))
	{
		if (i == 0 || j == 0 || j == (int)ft_strlen(map[i]) - 1
			|| i == get_arr_size(map) - 1)
			return (1);
		if (check_sides_null(map, i, j) || check_sides_space(map, i, j))
			return (1);
	}
	return (0);
}

int	check_map(char **map)
{
	int	i;
	int	j;
	int	player_found;

	i = -1;
	player_found = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (is_border(map, i, j) && map[i][j] != '1')
				return (-1);
			if (!is_allowed_char(map[i][j]))
				return (-1);
			if (player_found && is_player_direction(map[i][j]))
				return (-1);
			else if (is_player_direction(map[i][j]))
				player_found = 1;
		}
	}
	if (!player_found)
		return (-1);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;
// 	char	**map;
// 	t_lst	*node;
// 	t_lst	*lst;
// 	int		i;

// 	(void)argc;
// 	(void)argv;
// 	lst = NULL;
// 	fd = open("./map.cub", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd, 0);
// 		if (!line)
// 			break ;
// 		node = ft_lstnew((void *)line);
// 		ft_lstadd_back(&lst, node);
// 	}
// 	map = get_map(&lst);
// 	i = -1;
// 	while (map[++i])
// 		printf("%s\n", map[i]);
// 	if (check_map(map) == 0)
// 		printf("valid map content\n");
// 	else
// 		printf("not valid map\n");
// 	if (start_mlx(800, 800, map) == -1)
// 		return (-1);
// }
