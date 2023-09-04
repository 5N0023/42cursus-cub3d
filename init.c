/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:15:08 by mlektaib          #+#    #+#             */
/*   Updated: 2023/09/04 20:15:09 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

mlx_t	*initdefaultval(t_data *data_ptr)
{
	data_ptr->player.speed = 0.01;
	data_ptr->player.rotation = 0.01;
	data_ptr->player.wpress = 0;
	data_ptr->player.spress = 0;
	data_ptr->player.dpress = 0;
	data_ptr->player.apress = 0;
	data_ptr->player.gun.state = 0;
	data_ptr->player.speed = 0.08;
	data_ptr->mouse.x = data_ptr->player.angle;
	data_ptr->mouse.y = data_ptr->center;
	data_ptr->mouse.oldx = data_ptr->mouse.x;
	data_ptr->mouse.oldy = data_ptr->mouse.y;
	data_ptr->mouse.click = 0;
	data_ptr->mouse.anglemove = 0;
	data_ptr->mouse.centermove = 0;
	data_ptr->mouse.sensitivity = 0.1;
	data_ptr->center = 715;
	data_ptr->gamemode = NORMAL;
	data_ptr->state = STARTSCREEN;
	return (mlx_init(WINDOWW, WINDOWW, "CUB3D!", 0));
}
