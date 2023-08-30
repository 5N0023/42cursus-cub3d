#include "cub3D.h"

void normalize_angle(double *angle)
{
	if (*angle > 360)
		*angle -= 360;
	if (*angle < 0)
		*angle += 360;
}
	

void reneder_walls(t_data *data,double FOV, double angle)
{
	int k;
	double wallheight;
	int color;

	k = WINDOWW - 1;
	while (k >= 0)
	{
		hits(angle,data);
		wallheight = WINDOWW / (data->ray.distance * cos((angle - data->player.angle) * M_PI / 180.0));
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
		k--;
	}
}


void game(t_data *data)
{
	double	FOV;
	double	angle;
	double	draw;
	double	wallheight;
	int		color;

	move_player(data);	
	door_frames_setter(data);
	FOV = 60;
	normalize_angle(&data->player.angle);
	angle = data->player.angle - FOV / 2;
	normalize_angle(&data->player.angle);
	reneder_walls(data,FOV,angle);
	draw_cursor(data);
	draw_gun_normal(data);
	draw_map(data, 20, 0x00FF0F);
	
}