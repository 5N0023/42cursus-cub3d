#include "cub3D.h"

extern double	tester;

void	draw_wall(mlx_image_t *img, int pixelsline, double wallheight,
		t_data *data, int x)
{
	double	k;
	int		y;
	int		color;

	k = img->height / 2;
	y = data->center - 1;
	while (++y < data->center + wallheight / 2 && y < WINDOWW)
	{
		color = get_pixel(img, pixelsline, (int)k);
		k += 250 / wallheight;
		if (y >= 0 && y < WINDOWW && k >= 0 && k < 250)
			mlx_put_pixel(data->img, x, y, color);
	}
	y = data->center + 1;
	k = img->height / 2;
	while (--y > data->center - wallheight / 2 && y >= 0)
	{
		color = get_pixel(img, pixelsline, (int)k);
		k -= 250 / wallheight;
		if (y >= 0 && y < WINDOWW && k >= 0 && k < 250)
			mlx_put_pixel(data->img, x, y, color);
	}
}

mlx_image_t	*load_wall_texture_path(char *path, t_data *data)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(path);
	if (!texture)
		exit(1);
	img = mlx_texture_to_image(data->mlx, texture);
	mlx_resize_image(img, 250, 250);
	mlx_delete_texture(texture);
	return (img);
}

void	load_walls_textures(t_data *data)
{
	data->texture.nordimg = load_wall_texture_path(data->texture.nord, data);
	data->texture.sudimg = load_wall_texture_path(data->texture.sud, data);
	data->texture.eastimg = load_wall_texture_path(data->texture.east, data);
	data->texture.ouestimg = load_wall_texture_path(data->texture.ouest, data);
}

void	draw_ceil_floor(t_data *data, int x, double wallheight)
{
	int	i;
	int	y;

	i = 0;
	if (data->center - wallheight / 2 > 0)
	{
		i = data->center - wallheight / 2;
		y = -1;
		while (++y < i)
			if (y >= 0 && y < WINDOWW)
				mlx_put_pixel(data->img, x, y, data->ceilingcolor);
	}
	if (data->center + wallheight / 2 < WINDOWW)
	{
		i = data->center + wallheight / 2;
		y = i - 1;
		while (++y < WINDOWW)
			if (y >= 0 && y < WINDOWW)
				mlx_put_pixel(data->img, x, y, data->floorcolor);
	}
}

void	render_nord(t_data *data, int x, double wallheight)
{
	int	pixelsline;

	pixelsline = (int)((data->ray.x - (int)data->ray.x) * 250);
	draw_wall(data->texture.nordimg, pixelsline, wallheight, data, x);
	draw_ceil_floor(data, x, wallheight);
}
void	render_sud(t_data *data, int x, double wallheight)
{
	int	pixelsline;

	pixelsline = (int)((data->ray.x - (int)data->ray.x) * 250);
	draw_wall(data->texture.sudimg, pixelsline, wallheight, data, x);
	draw_ceil_floor(data, x, wallheight);
}

void	render_east(t_data *data, int x, double wallheight)
{
	int	pixelsline;

	pixelsline = ((int)((data->ray.y - (int)data->ray.y) * 250));
	draw_wall(data->texture.eastimg, pixelsline, wallheight, data, x);
	draw_ceil_floor(data, x, wallheight);
}

void	render_ouest(t_data *data, int x, double wallheight)
{
	int	pixelsline;

	pixelsline = ((int)((data->ray.y - (int)data->ray.y) * 250));
	draw_wall(data->texture.eastimg, pixelsline, wallheight, data, x);
	draw_ceil_floor(data, x, wallheight);
}

void	doors_rendering(t_data *data, int x, double wallheight)
{
	t_doorlist	*tmp;

	tmp = data->ray.doorlist;
	while (tmp)
	{
		tmp->doordistance *= cos((data->ray.angle - data->player.angle) * M_PI
			/ 180);
		wallheight = WINDOWW / tmp->doordistance;
		if (tmp->doorhitside == NS && tmp->doordistance <= (data->ray.distance
				* cos((data->ray.angle - data->player.angle) * M_PI / 180))
			+ 0.01)
			render_door_NS(data, x, wallheight, tmp);
		if (tmp->doorhitside == WE && tmp->doordistance <= (data->ray.distance
				* cos((data->ray.angle - data->player.angle) * M_PI / 180))
			+ 0.01)
			render_door_WE(data, x, wallheight, tmp);
		tmp = tmp->next;
	}
}

void	render_texture(t_data *data, int x, double wallheight)
{
	if (data->ray.texture == NORD)
		render_nord(data, x, wallheight);
	else if (data->ray.texture == OUEST)
		render_ouest(data, x, wallheight);
	else if (data->ray.texture == SUD)
		render_sud(data, x, wallheight);
	else if (data->ray.texture == EAST)
		render_east(data, x, wallheight);
	if (data->ray.doorlist && data->map.doors_count)
		doors_rendering(data, x, wallheight);
	free_door_list(data);
}
