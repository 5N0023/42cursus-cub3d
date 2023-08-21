#include "cub3D.h"

void game(t_data *data)
{
	double	FOV;
	double	angle;
	double	draw;
	int		k;
	double	distance;
	double	wallheight;
	int		color;
	move_player(data);	
	
	door_frames_setter(data);
	FOV = 60;
	while (data->player.angle >= 360)
		data->player.angle -= 360;
	while (data->player.angle < 0)
		data->player.angle += 360;
	angle = data->player.angle - FOV / 2;
	draw = 0;
	k = WINDOWW - 1;
	while (k >= 0)
	{
		hits(angle,data);
		distance = data->ray.distance * cosf((angle - data->player.angle) * M_PI / 180.0);
		wallheight = WINDOWW / distance;
		color = 0x964B00FF;
		if (data->ray.hitside == VERTICALE && data->ray.angle >= 0 && data->ray.angle <= 180)
			data->ray.texture = EAST;
		else if (data->ray.hitside == VERTICALE)
			data->ray.texture = OUEST;
		else if (data->ray.hitside == HORIZONTALE && data->ray.angle > 90 && data->ray.angle < 270)
			data->ray.texture = NORD;
		else
			data->ray.texture = SUD;
		render_texture(data, k, wallheight);
		angle += FOV / WINDOWW;
		draw += FOV / WINDOWW;
		k--;
	}
	data->texture.spriteframe++;
	if (data->texture.spriteframe == 29)
		data->texture.spriteframe = 0;
	draw_cursor(data);
	draw_gun_normal(data);
	draw_map(data, 20, 0x00FF0F);
	
}