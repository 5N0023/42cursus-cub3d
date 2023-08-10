#include"cub3D.h"


double			_hitx = 0;
double			_hity = 0;
double			_xray = -1;
double			_yray = -1;
int				_hit = 0;
double			_h_hitx = 0;
double			h_hity = 0;
double			v_hitx = 0;
double			v_hity = 0;


static void	castrayvertical(double x, double y, double angle, t_data *data)
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
	_xray = dx;
	_yray = dy;
	if (_xray < 0 || _xray > data->map.width || _yray < 0 || _yray > data->map.height)
	{
		_hit = 1;
		_xray = dx;
		_yray = dy;
		return ;
	}
	if ((pa >= 180 && pa <= 360))
		if (data->map.map[(int)dy][(int)dx - 1] == '1' || data->map.map[(int)dy][(int)dx - 1] == '*')
			_hit = 1;
	if (data->map.map[(int)dy][(int)dx] == '1' || data->map.map[(int)dy][(int)dx] == '*')
		_hit = 1;
	if (data->map.map[(int)dy][(int)dx] == 'd')
		add_back_to_doors(data,  dx,  dy, WE);
}

static void	castrayhorizontal(double x, double y, double angle, t_data *data)
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
	_xray = dx;
	_yray = dy;
	if (_xray < 0 || _xray > data->map.width || _yray < 0 || _yray > data->map.height)
	{
		_hit = 1;
		_xray = dx;
		_yray = dy;
		return ;
	}
	if (pa > 90 && pa < 270)
		{
			if (data->map.map[(int)dy - 1][(int)dx] == '1' || data->map.map[(int)dy - 1][(int)dx] == '*')
				_hit = 1;
		}
	if (data->map.map[(int)dy][(int)dx] == '1' || data->map.map[(int)dy][(int)dx] == '*')
		_hit = 1;
	if (data->map.map[(int)dy][(int)dx] == 'D')
		add_back_to_doors(data, dx, dy,NS);
	
}

double	collision(double angle,t_data *data)
{
	double	v_hitx;
	double	v_hity;
	double	_h_hitx;
	double	h_hity;
	double	vdistance;
	double	hdistance;
	double	distance;
	t_hit	v_hit;

	v_hit.hitx = WINDOWW;
	v_hit.hity = WINDOWW;
	v_hit.x = data->player.x;
	v_hit.hit = 0;
	v_hit.y = data->player.y;
	v_hit.dx = WINDOWW;
	v_hit.dy = WINDOWW;


	_xray = data->player.x;
	_yray = data->player.y;
	while(angle <= 0)
		angle += 360;
	while(angle >= 360)
		angle -= 360;
	data->ray.angle = angle;
	v_hitx = WINDOWW;
	v_hity = WINDOWW;
	_h_hitx = WINDOWW;
	h_hity = WINDOWW;
	_xray = data->player.x;
	_yray = data->player.y;
	_hit = 0;
	data->ray.doorlist = NULL;
	while (!_hit)
		castrayvertical(_xray, _yray, angle, data);
	v_hitx = _xray;
	v_hity = _yray;
	_xray = data->player.x;
	_yray = data->player.y;
	_hit = 0;
	while (!_hit)
		castrayhorizontal(_xray, _yray, angle, data);
	_h_hitx = _xray;
	h_hity = _yray;
	sort_door_list(data);
	vdistance = sqrtf(powf((v_hitx - data->player.x), 2) + powf((v_hity - data->player.y), 2));
	hdistance = sqrtf(powf((_h_hitx - data->player.x), 2) + powf((h_hity - data->player.y), 2));
	if (hdistance < vdistance)
	{
		data->ray.x = _h_hitx;
		data->ray.y = h_hity;
		data->ray.distance = hdistance;
		data->ray.hitside = HORIZONTALE;
	}
	else
	{
		data->ray.x = v_hitx;
		data->ray.y = v_hity;
		data->ray.distance = vdistance;
		data->ray.hitside = VERTICALE;
	}
	double ret;
	ret = data->ray.distance;
	return (ret);
}
