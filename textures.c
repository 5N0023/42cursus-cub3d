/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:23:30 by mlektaib          #+#    #+#             */
/*   Updated: 2023/09/04 22:42:22 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_wall(mlx_image_t *img, int pixelsline, double wallheight,
		t_data *data)
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
			mlx_put_pixel(data->img, data->ray.windowx, y, color);
	}
	y = data->center + 1;
	k = img->height / 2;
	while (--y > data->center - wallheight / 2 && y >= 0)
	{
		color = get_pixel(img, pixelsline, (int)k);
		k -= 250 / wallheight;
		if (y >= 0 && y < WINDOWW && k >= 0 && k < 250)
			mlx_put_pixel(data->img, data->ray.windowx, y, color);
	}
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
			render_door_ns(data, x, wallheight, tmp);
		if (tmp->doorhitside == WE && tmp->doordistance <= (data->ray.distance
				* cos((data->ray.angle - data->player.angle) * M_PI / 180))
			+ 0.01)
			render_door_we(data, x, wallheight, tmp);
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
