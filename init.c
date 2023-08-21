#include "cub3D.h"

void initdefaultval(t_data *data_ptr)
{
    data_ptr->player.speed = 0.01;
	data_ptr->player.rotation = 0.01;
	data_ptr->player.wpress = 0;
	data_ptr->player.spress = 0;
	data_ptr->player.dpress = 0;
	data_ptr->player.apress = 0;
	data_ptr->player.gun.state = 0;
	data_ptr->player.speed = 0.05;
	data_ptr->mouse.x = 0;
	data_ptr->mouse.y = 0;
	data_ptr->mouse.oldx = 0;
	data_ptr->mouse.oldy = 0;
	data_ptr->mouse.click = 0;
	data_ptr->mouse.anglemove = 0;
	data_ptr->mouse.centermove = 0;
	data_ptr->mouse.sensitivity = 0.1;
	data_ptr->center = 500;
	data_ptr->texture.spriteframe = 0;
}