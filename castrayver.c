/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castrayver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:05:48 by mlektaib          #+#    #+#             */
/*   Updated: 2023/09/04 20:08:57 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	find_dx(t_hit *vhit)
{
	if (vhit->angle <= 90 && vhit->angle >= 0)
		vhit->dx = floor(vhit->x) + 1;
	else if (vhit->angle >= 0 && vhit->angle <= 180)
		vhit->dx = floor(vhit->x) + 1;
	else if (vhit->angle >= 180 && vhit->angle <= 360)
	{
		if (vhit->dx == floor(vhit->x))
			vhit->dx = floor(vhit->x) - 1;
		else
			vhit->dx = floor(vhit->x);
	}
}

static void	find_dy(t_hit *vhit)
{
	if (vhit->angle != 0 && vhit->angle != 180 && vhit->angle != 360)
		vhit->dy = vhit->y + (vhit->dx - vhit->x)
			/ tan(vhit->angle * M_PI / 180.0);
	else if (vhit->angle == 0 || vhit->angle == 180 || vhit->angle == 360)
	{
		vhit->dx = vhit->x;
		if (vhit->angle == 0 || vhit->angle == 360)
			vhit->dy = floor(vhit->y) + 1;
		else
		{
			if (vhit->dy != floor(vhit->y))
				vhit->dy = floor(vhit->y);
			else
				vhit->dy = floor(vhit->y) - 1;
		}
	}
}

void	castrayvertical(t_hit *vhit, t_data *data)
{
	find_dx(vhit);
	find_dy(vhit);
	vhit->x = vhit->dx;
	vhit->y = vhit->dy;
	if (vhit->x <= 0 || vhit->x >= data->map.width || vhit->y <= 0
		|| vhit->y >= data->map.height)
	{
		vhit->hit = 1;
		return ;
	}
	if (vhit->angle >= 180 && vhit->angle <= 360)
		if (data->map.map[(int)vhit->dy][(int)vhit->dx - 1] == '1'
			|| data->map.map[(int)vhit->dy][(int)vhit->dx - 1] == '*')
			vhit->hit = 1;
	if (data->map.map[(int)vhit->dy][(int)vhit->dx] == '1'
		|| data->map.map[(int)vhit->dy][(int)vhit->dx] == '*')
		vhit->hit = 1;
	if (data->map.map[(int)vhit->y][(int)vhit->x] == 'd')
		add_back_to_doors(data, vhit->dx, vhit->dy, WE);
}
