#include"cub3D.h"


double			hitx = 0;
double			hity = 0;
double			xray = -1;
double			yray = -1;
int				hit = 0;
double			hhitx = 0;
double			hhity = 0;
double			vhitx = 0;
double			vhity = 0;


void	castrayvertical(double x, double y, double angle, t_data *data)
{
	double	pa;

	double dx, dy, radian;
	pa = angle;
	if (pa > 360)
		pa -= 360;
	if (pa < 0)
		pa += 360;
	if (pa <= 90 && pa >= 0)
		dx = (int)x + 1;
	else if (pa >= 0 && pa <= 180)
		dx = (int)x + 1;
	else if (pa >= 180 && pa <= 360)
	{
		if (dx == (int)x)
			dx = (int)x - 1;
		else
			dx = (int)x;
	}
	radian = pa * M_PI / 180.0;
	if (pa != 0 && pa != 180 && pa != 360)
		dy = y + (dx - x) / tanf(radian);
	else if (pa == 0 || pa == 180 || pa == 360)
	{
		dx = x;
		if (pa == 0 || pa == 360)
			dy = (int)y + 1;
		else
		{
			if (dy != (int)y)
				dy = (int)y;
			else
				dy = (int)y - 1;
		}
	}
	xray = dx;
	yray = dy;
	if (xray < 0 || xray > data->map.width || yray < 0 || yray > data->map.height)
	{
		hit = 1;
		xray = dx;
		yray = dy;
		return ;
	}
	if ((pa >= 180 && pa <= 360))
		if (data->map.map[(int)dy][(int)dx - 1] == '1' || data->map.map[(int)dy][(int)dx - 1] == '*')
			hit = 1;
	if (data->map.map[(int)dy][(int)dx] == '1' || data->map.map[(int)dy][(int)dx] == '*')
		hit = 1;
	if (data->map.map[(int)dy][(int)dx] == 'd'  && data->ray.doorhit == 0)
	{
		data->ray.doorhit = 1;
		data->ray.doorhitx = dx;
		data->ray.doorhity = dy;
		data->ray.doorhitside = WE;
	}
}

void	castrayhorizontal(double x, double y, double angle, t_data *data)
{
	double	pa;

	double dx, dy, radian;
	pa = angle;
	if (pa >= 360)
		pa -= 360;
	else if (pa < 0)
		pa += 360;
	radian = pa * M_PI / 180.0;
	if (pa > 90 && pa < 270)
	{
		if (dy == (int)y)
			dy = (int)y - 1;
		else
			dy = (int)y;
	}
	else
		dy = (int)y + 1;
	if (pa != 90 && pa != 270)
	{
		dx = x + (dy - y) * tanf(radian);
	}
	else
	{
		dy = y;
		if (pa == 90)
			dx = (int)x + 1;
		else if (dx != (int)(x))
			dx = (int)x;
		else
		{
			if (dx == (int)x)
				dx = (int)x - 1;
			else
				dx = (int)x;
		}
	}
	xray = dx;
	yray = dy;
	if (xray < 0 || xray > data->map.width || yray < 0 || yray > data->map.height)
	{
		hit = 1;
		xray = dx;
		yray = dy;
		return ;
	}
	if (pa > 90 && pa < 270)
		{
			if (data->map.map[(int)dy - 1][(int)dx] == '1' || data->map.map[(int)dy - 1][(int)dx] == '*')
				hit = 1;
		}
	if (data->map.map[(int)dy][(int)dx] == '1' || data->map.map[(int)dy][(int)dx] == '*')
		hit = 1;
	if (data->map.map[(int)dy][(int)dx] == 'D' && data->ray.doorhit == 0)
	{
		data->ray.doorhit = 1;
		data->ray.doorhitx = dx;
		data->ray.doorhity = dy;
		data->ray.doorhitside = NS;
	}
	
}

double	hits(double angle,t_data *data)
{
	double	vhitx;
	double	vhity;
	double	hhitx;
	double	hhity;
	double	vdistance;
	double	hdistance;
	double	distance;
	t_hit	vhit;

	vhit.hitx = WINDOWW;
	vhit.hity = WINDOWW;
	vhit.x = data->player.x;
	vhit.hit = 0;
	vhit.y = data->player.y;
	vhit.dx = WINDOWW;
	vhit.dy = WINDOWW;
	data->ray.doorhit = 0;


	xray = data->player.x;
	yray = data->player.y;
	while(angle <= 0)
		angle += 360;
	while(angle >= 360)
		angle -= 360;
	data->ray.angle = angle;
	vhitx = WINDOWW;
	vhity = WINDOWW;
	hhitx = WINDOWW;
	hhity = WINDOWW;
	xray = data->player.x;
	yray = data->player.y;
	hit = 0;
	while (!hit)
		castrayvertical(xray, yray, angle, data);
	vhitx = xray;
	vhity = yray;
	xray = data->player.x;
	yray = data->player.y;
	hit = 0;
	while (!hit)
		castrayhorizontal(xray, yray, angle, data);
	hhitx = xray;
	hhity = yray;
	data->ray.doordistance = sqrtf(powf((data->ray.doorhitx - data->player.x), 2) + powf((data->ray.doorhity - data->player.y), 2));
	vdistance = sqrtf(powf((vhitx - data->player.x), 2) + powf((vhity - data->player.y), 2));
	hdistance = sqrtf(powf((hhitx - data->player.x), 2) + powf((hhity - data->player.y), 2));
	if (hdistance < vdistance)
	{
		data->ray.x = hhitx;
		data->ray.y = hhity;
		data->ray.distance = hdistance;
		data->ray.hitside = HORIZONTALE;
	}
	else
	{
		data->ray.x = vhitx;
		data->ray.y = vhity;
		data->ray.distance = vdistance;
		data->ray.hitside = VERTICALE;
	}
	double ret;
	ret = data->ray.distance;
	if(data->ray.doorhitside == NS && data->ray.doorhit == 1)
	{
		if (door_state(data, (int)data->ray.doorhitx, (int)data->ray.doorhity) != OPENED)
			ret = data->ray.doordistance;
	}
	else if(data->ray.doorhitside == WE && data->ray.doorhit == 1)
	{
		if (door_state(data, (int)data->ray.doorhitx, (int)data->ray.doorhity) != OPENED)
				ret = data->ray.doordistance;
	}
	return (ret);
}
