#include "cub3D.h"

void movebackward(t_data *data)
{
	double	distance1;
	double	distance2;

		distance1 = collision(data->player.angle + 10 + 180,data);
		free_door_list(data);
		distance2 = collision(data->player.angle - 10 + 180,data);
		free_door_list(data);
		if (distance1 > 0.2 && distance2 > 0.2)
		{
		data->player.x += cos((data->player.angle + 90) * TO_RAD) * data->player.speed;
			data->player.y -= sinf((data->player.angle + 90) * TO_RAD) * data->player.speed;
		}
	}

void movefoward(t_data *data)
	{
	double	distance1;
	double	distance2;

		distance1 = collision(data->player.angle + 10, data);
		free_door_list(data);
		distance2 = collision(data->player.angle - 10,data);
		free_door_list(data);
		if (distance1 > 0.2 && distance2 > 0.2)
		{
		data->player.x -= cos((data->player.angle + 90) * TO_RAD) * data->player.speed;
			data->player.y += sinf((data->player.angle + 90) * TO_RAD) * data->player.speed;
		}
	}
void moveleft(t_data *data)
	{
	double	distance1;
	double	distance2;

		distance1 = collision(data->player.angle + 10 - 90,data);
		free_door_list(data);
		distance2 = collision(data->player.angle - 10 - 90,data);
		free_door_list(data);
		if (distance1 > 0.2 && distance2 > 0.2)
		{
		data->player.x -= cos((data->player.angle)*TO_RAD) * data->player.speed;
			data->player.y += sinf((data->player.angle)*TO_RAD) * data->player.speed;
		}
	}


void moveright(t_data *data)
	{
	double	distance1;
	double	distance2;

		distance1 = collision(data->player.angle + 10 + 90,data);
		free_door_list(data);
		distance2 = collision(data->player.angle - 10 + 90,data);
		free_door_list(data);
		if (distance1 > 0.2 && distance2 > 0.2)
		{
		data->player.x += cos((data->player.angle)*TO_RAD) * data->player.speed;
			data->player.y -= sinf((data->player.angle)*TO_RAD) * data->player.speed;
		}
	}

void	move_player(t_data *data)
{
	normalize_angle(&data->player.angle);
	if (data->player.spress)
		movebackward(data);
	if (data->player.wpress)
		movefoward(data);
	if (data->player.dpress)
		moveleft(data);
	if (data->player.apress)
		moveright(data);
			data->player.angle = (data->mouse.x * -data->mouse.sensitivity);
    data->center  = 715 + (data->mouse.y * -(data->mouse.sensitivity * 5));
	if(data->center <= -500)
	{
		data->center = -500;
		mlx_set_mouse_pos(data->mlx,data->mouse.x, data->mouse.y);
	}
	if(data->center >= WINDOWW + 500)
	{
		data->center = WINDOWW + 500;
		mlx_set_mouse_pos(data->mlx, data->mouse.x, data->mouse.y);
	}
	if(data->mouse.click == 1 && data->player.gun.state == 0)
		data->player.gun.state = SHOOT;
	data->mouse.oldx = data->mouse.x;
	data->mouse.oldy = data->mouse.y;
}