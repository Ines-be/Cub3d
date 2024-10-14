/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyboard_inputs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:48:41 by kipouliq          #+#    #+#             */
/*   Updated: 2024/10/14 17:48:24 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int move_character_up(void *param)
{ 
    (void) param;
    printf("moving character up\n");
    return (0);
}

int move_character_down(void *param)
{
    (void) param;
    printf("moving character down\n");
    return (0);
}

int move_character_left(void *param)
{
    (void) param;
    printf("moving character left\n");
    return (0);
}

int move_character_right(void *param)
{
    (void) param;
    printf("moving character right\n");
    return (0);
}

int move_direction_left(void *param)
{
    (void) param;
    printf("moving direction left\n");
    return (0);
}

int move_direction_right(void *param)
{
    (void) param;
    printf("moving direction right\n");
    return (0);
}

int move_direction(int key, void *param)
{
    if (key == LEFT)
        return (move_direction_left(param));
    else if (key == RIGHT)
        return (move_direction_right(param));
    return (0);
}

int move_character(int key, void *param)
{
    (void) param;
    if (key == W)
        return (move_character_up(param));
    else if (key == S)
        return (move_character_down(param));
    else if (key == A)
        return (move_character_left(param));
    else if (key == D)
        return (move_character_right(param));
    return (0);
}

int handle_keyboard_inputs(int key, void *param)
{
    (void) param;
    printf("key == %d\n", key);
    if (key == LEFT || key == RIGHT)
        return (move_direction(key, param));
    else if (key == W || key == A || key == S || key == D)
        return (move_character(key, param));
    else if (key == ESCAPE)
        return (quit_cube(param));
    printf("key = %d\n", key);
    return (0);
}
