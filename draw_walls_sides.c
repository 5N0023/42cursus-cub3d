/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls_sides.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:40:02 by mlektaib          #+#    #+#             */
/*   Updated: 2023/09/04 22:40:50 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render_nord(t_data *data, int x, double wallheight)
{
	int	pixelsline;

	pixelsline = (int)((data->ray.x - (int)data->ray.x) * 250);
	data->ray.windowx = x;
	draw_wall(data->texture.nordimg, pixelsline, wallheight, data);
	draw_ceil_floor(data, x, wallheight);
}

void	render_sud(t_data *data, int x, double wallheight)
{
	int	pixelsline;

	pixelsline = (int)((data->ray.x - (int)data->ray.x) * 250);
	data->ray.windowx = x;
	draw_wall(data->texture.sudimg, pixelsline, wallheight, data);
	draw_ceil_floor(data, x, wallheight);
}

void	render_east(t_data *data, int x, double wallheight)
{
	int	pixelsline;

	pixelsline = ((int)((data->ray.y - (int)data->ray.y) * 250));
	data->ray.windowx = x;
	draw_wall(data->texture.eastimg, pixelsline, wallheight, data);
	draw_ceil_floor(data, x, wallheight);
}

void	render_ouest(t_data *data, int x, double wallheight)
{
	int	pixelsline;

	pixelsline = ((int)((data->ray.y - (int)data->ray.y) * 250));
	data->ray.windowx = x;
	draw_wall(data->texture.eastimg, pixelsline, wallheight, data);
	draw_ceil_floor(data, x, wallheight);
}
