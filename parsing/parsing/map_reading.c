/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:06:05 by mjarboua          #+#    #+#             */
/*   Updated: 2023/09/04 23:45:32 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

char	**map_reader(char *file_name)
{
	int		i;
	char	**map;
	int		j;
	int		file;

	i = get_map_len(file_name);
	j = 0;
	file = open(file_name, O_RDONLY);
	if (file == -1)
		return (printf("error in opening '%s'\n", file_name), exit(1), NULL);
	map = malloc(sizeof(char *) * (i + 1));
	if (!map)
		return (printf("error in allocation (malloc failed)")
			, free(map), exit(1), NULL);
	while (j < i)
	{
		map[j] = get_next_line(file);
		_replace(map[j]);
		j++;
	}
	map[j] = NULL;
	return (close(file), map);
}

int	get_player_direction(char **m)
{
	int	count;
	int	direction;
	int	i[2];

	i[I] = -1;
	direction = 0;
	count = 0;
	while (m[++i[I]])
	{
		i[J] = -1;
		while (m[i[I]][++i[J]])
		{
			if (m[i[I]][i[J]] == 'E' || m[i[I]][i[J]] == 'S'
				|| m[i[I]][i[J]] == 'N' || m[i[I]][i[J]] == 'W')
			{
				direction = m[i[I]][i[J]];
				count++;
			}
		}
	}
	if (count != 1)
		return (-1);
	return (direction);
}
