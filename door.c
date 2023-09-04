/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:11:37 by mlektaib          #+#    #+#             */
/*   Updated: 2023/09/04 23:20:09 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_door_frame(t_doorlist *tmp, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map.doors_count)
	{
		if (data->map.doors[i].x == (int)tmp->doorhitx
			&& data->map.doors[i].y == (int)tmp->doorhity)
			return (data->map.doors[i].frame);
		i++;
	}
	return (0);
}

int	door_state(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->map.doors_count)
	{
		if (data->map.doors[i].x == x && data->map.doors[i].y == y)
		{
			return (data->map.doors[i].state);
		}
		i++;
	}
	return (0);
}

void	door_textures(t_data *data)
{
	mlx_texture_t	*texture;
	int				i;
	char			*path;

	i = 0;
	data->texture.door = malloc(sizeof(mlx_image_t *) * 35);
	path = ft_strdup("textures/door/frame-000.png");
	while (i < 35)
	{
		path[21] = (i + 1) / 10 + '0';
		path[22] = (i + 1) % 10 + '0';
		texture = mlx_load_png(path);
		if (!texture)
			exit(1);
		data->texture.door[i] = mlx_texture_to_image(data->mlx, texture);
		mlx_resize_image(data->texture.door[i], 250, 250);
		mlx_delete_texture(texture);
		i++;
	}
	free(path);
}

void	door_frames_setter(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map.doors_count)
	{
		if (data->map.doors[i].state == CLOSED)
			data->map.doors[i].frame = 0;
		else if (data->map.doors[i].state == OPENING)
			data->map.doors[i].frame++;
		else if (data->map.doors[i].state == OPENED)
			data->map.doors[i].frame = 34;
		else if (data->map.doors[i].state == CLOSING)
			data->map.doors[i].frame--;
		if (data->map.doors[i].frame <= 0)
		{
			data->map.doors[i].frame = 0;
			data->map.doors[i].state = CLOSED;
		}
		if (data->map.doors[i].frame > 34)
		{
			data->map.doors[i].frame = 34;
			data->map.doors[i].state = OPENED;
		}
		i++;
	}
}

void	door_remote(t_data *data, int i, t_doorlist *tmp)
{
	if (data->map.doors[i].x == (int)tmp->doorhitx
		&& data->map.doors[i].y == (int)tmp->doorhity && tmp->doordistance < 3
		&& tmp->doordistance > 0.15)
	{
		if (data->map.doors[i].state == OPENING)
			data->map.doors[i].state = CLOSING;
		else if (data->map.doors[i].state == CLOSING)
			data->map.doors[i].state = OPENING;
		else if (data->map.doors[i].state == CLOSED)
			data->map.doors[i].state = OPENING;
		else if (data->map.doors[i].state == OPENED)
			data->map.doors[i].state = CLOSING;
	}
}
