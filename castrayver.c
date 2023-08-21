#include "cub3D.h"

static void find_dx(t_hit *vhit)
{
	if (vhit->angle <= 90 && vhit->angle >= 0)
		vhit->dx = (int)vhit->x + 1;
	else if (vhit->angle >= 0 && vhit->angle <= 180)
		vhit->dx = (int)vhit->x + 1;
	else if (vhit->angle >= 180 && vhit->angle <= 360)
	{
		if (vhit->dx == (int)vhit->x)
			vhit->dx = (int)vhit->x - 1;
		else
			vhit->dx = (int)vhit->x;
	}
}

static void find_dy(t_hit *vhit)
{
	if (vhit->angle != 0 && vhit->angle != 180 && vhit->angle != 360)
		vhit->dy = vhit->y + (vhit->dx - vhit->x) / tanf(vhit->angle * M_PI / 180.0);
	else if (vhit->angle == 0 || vhit->angle == 180 || vhit->angle == 360)
	{
		vhit->dx = vhit->x;
		if (vhit->angle == 0 || vhit->angle == 360)
			vhit->dy = (int)vhit->y + 1;
		else
		{
			if (vhit->dy != (int)vhit->y)
				vhit->dy = (int)vhit->y;
			else
				vhit->dy = (int)vhit->y - 1;
		}
	}
}

void	castrayvertical(t_hit *vhit, t_data *data)
{
    find_dx(vhit);
	find_dy(vhit);
	vhit->x = vhit->dx;
	vhit->y = vhit->dy;
	if (vhit->x < 0 || vhit->x > data->map.width || vhit->y < 0 || vhit->y > data->map.height)
	{
		vhit->hit = 1;
		return ;
	}
	if (vhit->angle  >= 180 && vhit->angle  <= 360)
		if (data->map.map[(int)vhit->dy][(int)vhit->dx - 1] == '1' || data->map.map[(int)vhit->dy][(int)vhit->dx - 1] == '*')
			vhit->hit = 1;
	if (data->map.map[(int)vhit->dy][(int)vhit->dx] == '1' || data->map.map[(int)vhit->dy][(int)vhit->dx] == '*')
		vhit->hit = 1;
	if (data->map.map[(int)vhit->dy][(int)vhit->dx] == 'd')
		add_back_to_doors(data,  vhit->dx,  vhit->dy, WE);
	if (vhit->angle  >= 180 && vhit->angle  <= 360)
		if (data->map.map[(int)vhit->dy][(int)vhit->dx - 1] == 'B')
			add_back_to_sprites(data,  vhit->dx - 1,  vhit->dy, OUEST);
	if (data->map.map[(int)vhit->dy][(int)vhit->dx] == 'B')
		add_back_to_sprites(data,  vhit->dx,  vhit->dy, EAST);
	
}
