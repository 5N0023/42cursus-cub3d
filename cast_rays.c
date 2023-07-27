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
	if ((pa >= 180 && pa <= 360) || pa ==0)
	{
		if (data->map.map[(int)dy][(int)dx - 1] != '0')
			hit = 1;
	}
		
	if (data->map.map[(int)dy][(int)dx] != '0')
	{
		hit = 1;
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
	if (pa >= 0 && pa < 90)
		dy = (int)y + 1;
	else if (pa > 90 && pa < 270)
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
	if (pa >= 90 && pa <= 270)
	{
		if (data->map.map[(int)dy - 1][(int)dx] != '0')
			hit = 1;
	}
	if (data->map.map[(int)dy][(int)dx] != '0')
		hit = 1;
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


	xray = data->player.x;
	yray = data->player.y;
	while(angle < 0)
		angle += 360;
	while(angle > 360)
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
	
	vdistance = sqrtf(powf((vhitx - data->player.x), 2) + powf((vhity - data->player.y), 2));
	hdistance = sqrtf(powf((hhitx - data->player.x), 2) + powf((hhity - data->player.y), 2));
	if (hdistance <= vdistance)
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
	return (data->ray.distance);
}
