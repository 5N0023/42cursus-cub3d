#include "cub3D.h"

void	init_collision(t_hit *vhit, t_hit *hhit, t_data *data, double angle)
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

void	pick_col_distance(t_data *data, t_hit vhit, t_hit hhit)
{
	if (hhit.distance < vhit.distance)
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

double	pick_return_value(t_data *data)
{
	double	ret;

	ret = data->ray.distance;
	if (data->ray.doorlist)
	{
		if (data->ray.doorlist->doordistance < data->ray.distance
			&& door_state(data, data->ray.doorlist->doorhitx,
				data->ray.doorlist->doorhity) != OPENED)
			ret = data->ray.doorlist->doordistance;
		if (data->ray.doorlist->doordistance < data->ray.distance
			&& door_state(data, data->ray.doorlist->doorhitx,
				data->ray.doorlist->doorhity) == OPENED)
		{
			if (data->ray.doorlist->doorhitside == WE
				&& (data->ray.doorlist->doorhity
					- floor(data->ray.doorlist->doorhity) < 0.2
					|| data->ray.doorlist->doorhity
					- floor(data->ray.doorlist->doorhity) > 0.8))
				ret = data->ray.doorlist->doordistance;
			if (data->ray.doorlist->doorhitside == NS
				&& (data->ray.doorlist->doorhitx
					- floor(data->ray.doorlist->doorhitx) < 0.2
					|| data->ray.doorlist->doorhitx
					- floor(data->ray.doorlist->doorhitx) > 0.8))
				ret = data->ray.doorlist->doordistance;
		}
	}
	return (ret);
}

double	collision(double angle, t_data *data)
{
	t_hit	vhit;
	t_hit	hhit;

	while (angle <= 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;
	init_collision(&vhit, &hhit, data, angle);
	data->ray.angle = angle;
	data->ray.doorlist = NULL;
	while (!vhit.hit)
		castrayvertical(&vhit, data);
	while (!hhit.hit)
		castrayhorizontal(&hhit, data);
	sort_door_list(data, 0);
	vhit.distance = sqrtf(powf((vhit.x - data->player.x), 2) + powf((vhit.y
					- data->player.y), 2));
	hhit.distance = sqrtf(powf((hhit.x - data->player.x), 2) + powf((hhit.y
					- data->player.y), 2));
	pick_col_distance(data, vhit, hhit);
	return (pick_return_value(data));
}
