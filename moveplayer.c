#include "cub3D.h"

void	move_player(t_data *data)
{

	double	distance1;
	double	distance2;
	while (data->player.angle >= 360)
		data->player.angle -= 360;
	while (data->player.angle < 0)
		data->player.angle += 360;

	if (data->player.spress)
	{
		distance1 = collision(data->player.angle + 10 + 180,data);
		free_door_list(data);
		free_sprites_list(data);
		distance2 = collision(data->player.angle - 10 + 180,data);
		free_door_list(data);
		free_sprites_list(data);
		if (distance1 > 0.2 && distance2 > 0.2)
		{
			data->player.x += cosf((data->player.angle + 90) * M_PI / 180.0) * data->player.speed;
			data->player.y -= sinf((data->player.angle + 90) * M_PI / 180.0) * data->player.speed;
		}
	}
	if (data->player.wpress)
	{
		distance1 = collision(data->player.angle + 10, data);
		free_door_list(data);
		free_sprites_list(data);
		distance2 = collision(data->player.angle - 10,data);
		free_door_list(data);
		free_sprites_list(data);
		if (distance1 > 0.2 && distance2 > 0.2)
		{
			data->player.x -= cosf((data->player.angle + 90) * M_PI / 180.0) * data->player.speed;
			data->player.y += sinf((data->player.angle + 90) * M_PI / 180.0) * data->player.speed;
		}
	}
	if (data->player.dpress)
	{
		distance1 = collision(data->player.angle + 10 - 90,data);
		free_door_list(data);
		free_sprites_list(data);
		distance2 = collision(data->player.angle - 10 - 90,data);
		free_door_list(data);
		free_sprites_list(data);
		if (distance1 > 0.2 && distance2 > 0.2)
		{
			data->player.x -= cosf((data->player.angle)*M_PI / 180.0) * data->player.speed;
			data->player.y += sinf((data->player.angle)*M_PI / 180.0) * data->player.speed;
		}
	}
	if (data->player.apress)
	{
		distance1 = collision(data->player.angle + 10 + 90,data);
		free_door_list(data);
		free_sprites_list(data);
		distance2 = collision(data->player.angle - 10 + 90,data);
		free_door_list(data);
		free_sprites_list(data);
		if (distance1 > 0.2 && distance2 > 0.2)
		{
			data->player.x += cosf((data->player.angle)*M_PI / 180.0) * data->player.speed;
			data->player.y -= sinf((data->player.angle)*M_PI / 180.0) * data->player.speed;
		}
	}
	if(data->mouse.oldx != data->mouse.x)
			data->player.angle = (data->mouse.x * -data->mouse.sensitivity);
    data->center  = WINDOWW / 2 + data->mouse.y * -data->mouse.sensitivity;
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
	while (data->player.angle >= 360)
		data->player.angle -= 360;
	while (data->player.angle < 0)
		data->player.angle += 360;
}