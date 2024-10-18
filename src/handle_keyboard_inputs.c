/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyboard_inputs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:48:41 by kipouliq          #+#    #+#             */
/*   Updated: 2024/10/18 18:12:02 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int move_direction_left(t_cub *cub)
{
    printf("cub vec dir x = %f\n", cub->player.dir.x);  
    printf("cub vec dir y = %f\n", cub->player.dir.y);
    cub->player.dir = rotate_vector(cub->player.dir, 1.5708);
    cub->player.fov_l = rotate_vector(cub->player.fov_l, 1.5708);
    cub->player.fov_r = rotate_vector(cub->player.fov_r, 1.5708);
    printf("cub vec dir x = %f\n", cub->player.dir.x);  
    printf("cub vec dir y = %f\n", cub->player.dir.y);
    refresh_raycasting(cub);
    return (0);
}

int move_direction_right(t_cub *cub)
{
    (void) cub;
    printf("moving direction right\n");
    return (0);
}

int move_direction(int key, t_cub *cub)
{
    if (key == LEFT)
        return (move_direction_left(cub));
    else if (key == RIGHT)
        return (move_direction_right(cub));
    return (0);
}

int move_character(int key, t_cub *cub)
{
    if (key == W)
        return (move_character_up(cub));
    else if (key == S)
        return (move_character_down(cub));
    else if (key == A)
        return (move_character_left(cub));
    else if (key == D)
        return (move_character_right(cub));
    return (0);
}

int handle_keyboard_inputs(int key, t_cub *cub)
{
    if (key == LEFT || key == RIGHT)
        return (move_direction(key, cub));
    else if (key == W || key == A || key == S || key == D)
        return (move_character(key, cub));
    else if (key == ESCAPE)
        return (quit_cube(cub));
    return (0);
}
