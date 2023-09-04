/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:20:20 by mlektaib          #+#    #+#             */
/*   Updated: 2023/09/04 22:38:16 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_door_top(t_data *data, double wallheight, int frame,
		int pixelsline)
{
	double	k;
	double	y;
	int		color;

	k = data->texture.door[frame]->height / 2;
	y = data->center;
	while (y < data->center + wallheight / 2 && y < WINDOWW)
	{
		color = get_pixel(data->texture.door[frame], pixelsline, (int)k);
		k += 250 / wallheight;
		if (k >= 250)
			k = 249;
		if (y >= 0 && y < WINDOWW && color)
			mlx_put_pixel(data->img, data->ray.windowx, y, color);
		y++;
	}
}

void	draw_door_bot(t_data *data, double wallheight, int frame,
		int pixelsline)
{
	double	k;
	double	y;
	int		color;

	y = data->center;
	k = data->texture.door[frame]->height / 2;
	while (y > data->center - wallheight / 2 && y >= 0)
	{
		color = get_pixel(data->texture.door[frame], pixelsline, (int)k);
		k -= 250 / wallheight;
		if (k < 0)
			k = 0;
		if (y >= 0 && y < WINDOWW && color)
			mlx_put_pixel(data->img, data->ray.windowx, y, color);
		y--;
	}
}

void	render_door_ns(t_data *data, int x, double wallheight, t_doorlist *tmp)
{
	int	pixelsline;
	int	frame;

	data->ray.windowx = x;
	pixelsline = (int)((tmp->doorhitx - (int)tmp->doorhitx) * 250);
	frame = get_door_frame(tmp, data);
	draw_door_top(data, wallheight, frame, pixelsline);
	draw_door_bot(data, wallheight, frame, pixelsline);
}

void	render_door_we(t_data *data, int x, double wallheight, t_doorlist *tmp)
{
	int	pixelsline;
	int	frame;

	data->ray.windowx = x;
	pixelsline = (int)((tmp->doorhity - (int)tmp->doorhity) * 250);
	frame = get_door_frame(tmp, data);
	draw_door_top(data, wallheight, frame, pixelsline);
	draw_door_bot(data, wallheight, frame, pixelsline);
}
