/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:14:10 by inbennou          #+#    #+#             */
/*   Updated: 2024/10/14 17:18:29 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_cub
{
	char	*no_text;
	char	*so_text;
	char	*ea_text;
	char	*we_text;
	int		c_color;
	int		f_color;
}			t_cub;

// parsing
void		name_check(char *str);
t_list		*get_file(int fd);
void		elems_check(char **split_elem, t_list *start, t_cub *cub);
bool		get_elems(t_list *file_content, t_cub *cub, t_list *start);
void		parsing(int ac, char **av, t_list **start, t_cub *cub);

// init
void		init_cub(t_cub *cub);

// add text
void		add_texture(char **split_elem, t_list *file_content, t_list *start,
				t_cub *cub);
int			add_north(char **tab, t_list *start, t_cub *cub);
int			add_south(char **tab, t_list *start, t_cub *cub);
int			add_east(char **tab, t_list *start, t_cub *cub);
int			add_west(char **tab, t_list *start, t_cub *cub);

// get color
int			get_int(char **split_elem, t_list *start, t_cub *cub, char *color);
void		get_color(char **split_elem, t_list *start, t_cub *cub, char id);

// utils
bool		is_space(char c);
void		free_line(char *line);
void		free_cub(t_cub *cub);
bool		is_empty(char *str);
bool		is_elem(char *str);

// utils2
bool		is_number(char c);
bool		only_numbers(char *str);
int			create_rgb(int r, int g, int b);
int			pos_atoi(char *str);

// errors
void		map_error(int fd, char *msg, t_list *file_content);
void		texture_error(char **tab, t_list *start, t_cub *cub, char *msg);

// ft_split
char		**ft_split(const char *s, char c);

#endif