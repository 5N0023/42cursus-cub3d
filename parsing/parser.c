/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:20:53 by mjarboua          #+#    #+#             */
/*   Updated: 2023/09/06 15:22:34 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

void fill_doors_info(t_data *data, size_t i, size_t j)
{
	static int count = 0;
	if(data->map.map[i][j] == 'D')
		{
			data->map.doors[count].x = j;
			data->map.doors[count].y = i;
			data->map.doors[count].state = CLOSED;
			data->map.doors[count].frame = 0;
			data->map.doors[count].side = NS;
			count++;
		}
	else if(data->map.map[i][j] == 'd')
		{
			data->map.doors[count].x = j;
			data->map.doors[count].y = i;
			data->map.doors[count].state = CLOSED;
			data->map.doors[count].frame = 0;
			data->map.doors[count].side = WE;
			count++;
		}
}

int	doors_count(t_data *data)
{
	int count;
	size_t i;
	size_t j;

	count = 0;
	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (data->map.map[i][j] == 'D' || data->map.map[i][j] == 'd')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int find_doors(t_data *data)
{
	size_t i;
	size_t j;
	
	i=0;
	data->map.doors_count = doors_count(data);
	if(data->map.doors_count == 0)
		return (0);
	data->map.doors = malloc(sizeof(t_doors) * data->map.doors_count);
	while(i < data->map.height)
	{
		j = 0;
		while(j < data->map.width)
		{
			if (data->map.map[i][j] == 'D' || data->map.map[i][j] == 'd')
				fill_doors_info(data, i, j);
			j++;
		}
		i++;
	}
	return (0);
}

int set_player_pos(t_data *data, size_t i, size_t j)
{
	data->player.x = j+0.5;
	data->player.y = i + 0.5;
	if(data->map.map[i][j] == 'N')
		data->player.angle = 180;
	else if(data->map.map[i][j] == 'S')
		data->player.angle = 0;
	else if(data->map.map[i][j] == 'E')
		data->player.angle = 90;
	else if(data->map.map[i][j] == 'W')
		data->player.angle = 270;
	data->map.map[i][j] = '0';
	return (0);
}

int find_player_pos(t_data *data)
{
	size_t i;
	size_t j;

	i = 0;
	while(i < data->map.height)
	{
		j = 0;
		while(j < data->map.width)
		{
			if (data->map.map[i][j] == 'N' || data->map.map[i][j] == 'S' || data->map.map[i][j] == 'E' || data->map.map[i][j] == 'W')
				return (set_player_pos(data, i, j));
			j++;
		}
		i++;
	}
	return (1);
}

int	parser(int c, char **v, t_data *data)
{
	t_pars *pars;
	
	if (c == 1)
		return (printf("you will have to give the map path as an argument\n"), 1);
	pars = ft_map_parser(v[1]);
	if (!pars)
			return (1);
	data->map.map = pars->map.map;
	data->map.width = pars->map.width;
	data->map.height = pars->map.height;
	data->floorcolor = pars->floorcolor;
	data->ceilingcolor = pars->ceilingcolor;
	data->texture.sud = pars->south;
	data->texture.ouest = pars->west;
	data->texture.east = pars->east;
	data->texture.nord = pars->north;
	find_player_pos(data);
	find_doors(data);
	free(pars);
	return (0);
}