/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:44:36 by kipouliq          #+#    #+#             */
/*   Updated: 2024/10/23 15:52:28 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int move_character_up(t_cub *cub)
{
    cub->player.pos.y += 1;
    refresh_raycasting(cub);
    return (0);
}

int move_character_down(t_cub *cub)
{
    cub->player.pos.y -= 1;
    refresh_raycasting(cub);
    return (0);
}

int move_character_left(t_cub *cub)
{
    cub->player.pos.x -= 1;
    refresh_raycasting(cub);
    return (0);
}

int move_character_right(t_cub *cub)
{
    cub->player.pos.x += 1;
    refresh_raycasting(cub);
    return (0);
}
