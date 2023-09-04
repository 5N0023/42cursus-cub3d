#include "cub3D.h"

void	reload_animation(t_data *data, int *f)
{
	size_t	i;
	size_t	j;
	int	pixel;

	i = 0;
	while (i < data->player.gun.normal.gunreload[*f / 2]->width)
	{
		j = 0;
		while (j < data->player.gun.normal.gunreload[*f / 2]->height)
		{
			pixel = get_pixel(data->player.gun.normal.gunreload[*f / 2], i, j);
			if (pixel)
				mlx_put_pixel(data->img, i + 200, j + (WINDOWW
						- data->player.gun.normal.gunreload[*f / 2]->height),
					pixel);
			j++;
		}
		i++;
	}
	(*f)++;
	if (*f == 45 * 2)
	{
		data->player.gun.normal.bullet = 24;
		*f = 0;
		data->player.gun.state = 0;
	}
}

void	draw_bullets_count(t_data *data)
{
	size_t	i;
	size_t	j;
	int	pixel;

	i = 0;
	while (i < data->player.gun.normal.bullets[data->player.gun.normal.bullet]->height)
	{
		j = 0;
		while (j < data->player.gun.normal.bullets[data->player.gun.normal.bullet]->height)
		{
			pixel = get_pixel(data->player.gun.normal.bullets[data->player.gun.normal.bullet],
					i, j);
			if (pixel)
				mlx_put_pixel(data->img, i + 50, j + (WINDOWW
						- data->player.gun.normal.bullets[data->player.gun.normal.bullet]->height),
					pixel);
			j++;
		}
		i++;
	}
}

void	shoot_animation(t_data *data, int *f, int *k)
{
	size_t	i;
	size_t	j;
	int	pixel;

	i = 0;
	while (i < data->player.gun.normal.gunshoot[*f]->width)
	{
		j = 0;
		while (j < data->player.gun.normal.gunshoot[*f]->height)
		{
			pixel = get_pixel(data->player.gun.normal.gunshoot[*f], i, j);
			if (pixel)
				mlx_put_pixel(data->img, i + 200, j + (WINDOWW
						- data->player.gun.normal.gunshoot[*f]->height), pixel);
			j++;
		}
		i++;
	}
	(*f)++;
	if (!*k)
	{
		data->player.gun.normal.bullet--;
		*k = 1;
	}
}

void	gun_texture(t_data *data, int *f, int *k)
{
	size_t	i;
	size_t	j;
	int	pixel;

	i = 0;
	*f = 0;
	*k = 0;
	while (i < data->player.gun.normal.gunshoot[5]->width)
	{
		j = 0;
		while (j < data->player.gun.normal.gunshoot[5]->height)
		{
			pixel = get_pixel(data->player.gun.normal.gunshoot[5], i, j);
			if (pixel)
				mlx_put_pixel(data->img, i + 200, j + (WINDOWW
						- data->player.gun.normal.gunshoot[5]->height), pixel);
			j++;
		}
		i++;
	}
	data->player.gun.state = 0;
}

void	draw_gun_normal(t_data *data)
{
	static int f;
	static int k;

	draw_bullets_count(data);
	if (data->player.gun.state == RELOAD && data->player.gun.normal.bullet < 24)
		reload_animation(data, &f);
	else if (data->player.gun.state == SHOOT
		&& data->player.gun.normal.bullet > 0)
	{
		shoot_animation(data, &f, &k);
		if (f == 10)
		{
			f = 0;
			k = 0;
			data->player.gun.state = 0;
		}
	}
	else
		gun_texture(data, &f, &k);
}