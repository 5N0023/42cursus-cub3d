/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 23:14:53 by mlektaib          #+#    #+#             */
/*   Updated: 2023/09/04 23:17:05 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_door_list(t_data *data)
{
	t_doorlist	*tmp;
	t_doorlist	*tmp2;

	tmp = data->ray.doorlist;
	if (!tmp)
		return ;
	while (tmp != NULL)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	data->ray.doorlist = NULL;
}

void	door_frames_controller(t_data *data)
{
	t_doorlist	*tmp;
	int			i;

	i = 0;
	hits(data->player.angle, data);
	tmp = data->ray.doorlist;
	if (tmp)
		while (tmp->next)
			tmp = tmp->next;
	if (!tmp)
	{
		free_door_list(data);
		return ;
	}
	if (tmp)
	{
		while (i < data->map.doors_count)
		{
			door_remote(data, i, tmp);
			i++;
		}
	}
	free_door_list(data);
}

void	add_back_to_doors(t_data *data, double x, double y, int side)
{
	t_doorlist	*new;
	t_doorlist	*last;

	new = malloc(sizeof(t_doorlist));
	new->doorhitx = x;
	new->doorhity = y;
	new->doorhitside = side;
	new->doordistance = sqrtf(pow(data->player.x - x, 2) + pow(data->player.y
				- y, 2));
	new->next = NULL;
	if (data->ray.doorlist == NULL)
	{
		data->ray.doorlist = new;
		return ;
	}
	last = data->ray.doorlist;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

void	swap(t_doorlist *a, t_doorlist *b)
{
	t_doorlist	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
