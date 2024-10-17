/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:44:36 by kipouliq          #+#    #+#             */
/*   Updated: 2024/10/17 17:29:34 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int move_character_up(t_cub *cub)
{
    cub->player_pos.y -= 2;
    refresh_raycasting(&cub->mlx_data, cub);
    return (0);
}

int move_character_down(t_cub *cub)
{
    cub->player_pos.y += 2;
    refresh_raycasting(&cub->mlx_data, cub);
    return (0);
}

int move_character_left(t_cub *cub)
{
    cub->player_pos.x -= 2;
    refresh_raycasting(&cub->mlx_data, cub);
    return (0);
}

int move_character_right(t_cub *cub)
{
    cub->player_pos.x += 2;
    refresh_raycasting(&cub->mlx_data, cub);
    return (0);
}
