/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:06:05 by mjarboua          #+#    #+#             */
/*   Updated: 2023/08/30 19:40:23 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

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
	while (j <= i)
	{
		map[j] = get_next_line(file);
		_replace(map[j]);
		j++;
	}
	return (close(file), map);
}
