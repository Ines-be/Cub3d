/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:14:10 by inbennou          #+#    #+#             */
/*   Updated: 2024/10/16 19:02:30 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define W 119
# define A 97
# define S 115
# define D 100
# define UP 65362
# define LEFT 65361
# define DOWN 65364
# define RIGHT 65363
# define ESCAPE 65307
# define ONE_UNIT 64

typedef struct s_window_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
}			t_window_mlx;

typedef struct s_mlx_img
{
	void	*img_ptr;
	char	*img_addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_mlx_img;

typedef struct s_cub
{
	char	*no_text;
	char	*so_text;
	char	*ea_text;
	char	*we_text;
	int		c_color;
	int		f_color;
}			t_cub;

// Map checking
int			check_sides_space(char **map, int i, int j);
int			is_map_char(char c);
int			is_player_direction(char c);
int			is_allowed_char(char c);
int			ft_is_space(char c);

// Minilibx display functions
int			start_mlx(int height, int width, char **map);

// Handle keyboard inputs
int			handle_keyboard_inputs(int key, void *param);

// Free functions
int			quit_cube(void *param);
int			error_exit(char *str);

// Map utils
void		free_arr_until_idx(char **arr, int idx);
int			get_arr_size(char **arr);
int			error_exit(char *str);

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
void		skip_elements(t_list **file_content);

// errors
void		map_error(int fd, char *msg, t_list *file_content);
void		texture_error(char **tab, t_list *start, t_cub *cub, char *msg);
void		color_error(char **tab, t_list *start, t_cub *cub, char *color);

// ft_split
char		**ft_split(const char *s, char c);

#endif