/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:04:07 by mlektaib          #+#    #+#             */
/*   Updated: 2023/09/04 20:08:10 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_hits(t_hit *vhit, t_hit *hhit, t_data *data, double angle)
{
	vhit->hitx = WINDOWW;
	vhit->hity = WINDOWW;
	vhit->x = data->player.x;
	vhit->hit = 0;
	vhit->y = data->player.y;
	vhit->dx = WINDOWW;
	vhit->dy = WINDOWW;
	vhit->xray = data->player.x;
	vhit->yray = data->player.y;
	vhit->angle = angle;
	hhit->hitx = WINDOWW;
	hhit->hity = WINDOWW;
	hhit->x = data->player.x;
	hhit->hit = 0;
	hhit->y = data->player.y;
	hhit->dx = WINDOWW;
	hhit->dy = WINDOWW;
	hhit->xray = data->player.x;
	hhit->yray = data->player.y;
	hhit->angle = angle;
}

void	pick_distance(t_data *data, t_hit vhit, t_hit hhit, double angle)
{
	if ((hhit.distance * cos((angle - data->player.angle)
				* M_PI / 180.0) < vhit.distance 
			* cos((angle - data->player.angle)
				* M_PI / 180.0)) || data->ray.angle == 0
		|| data->ray.angle == 180)
	{
		data->ray.x = hhit.x;
		data->ray.y = hhit.y;
		data->ray.distance = hhit.distance;
		data->ray.hitside = HORIZONTALE;
	}
	else
	{
		data->ray.x = vhit.x;
		data->ray.y = vhit.y;
		data->ray.distance = vhit.distance;
		data->ray.hitside = VERTICALE;
	}
}

double	hits(double angle, t_data *data)
{
	t_hit	vhit;
	t_hit	hhit;

	while (angle <= 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;
	init_hits(&vhit, &hhit, data, angle);
	data->ray.angle = angle;
	data->ray.doorlist = NULL;
	while (!hhit.hit)
		castrayhorizontal(&hhit, data);
	while (!vhit.hit)
		castrayvertical(&vhit, data);
	sort_door_list(data, 1);
	vhit.distance = sqrtf(powf((vhit.x - data->player.x), 2) + powf((vhit.y
					- data->player.y), 2));
	hhit.distance = sqrtf(powf((hhit.x - data->player.x), 2) + powf((hhit.y
					- data->player.y), 2));
	pick_distance(data, vhit, hhit, angle);
	return (data->ray.distance);
}
