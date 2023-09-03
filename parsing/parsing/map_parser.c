/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:24:25 by mjarboua          #+#    #+#             */
/*   Updated: 2023/09/02 23:32:44 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	skip_spaces_and_compare(char *line, char *txt)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (1);
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_strncmp(line + i, txt, ft_strlen(txt)) == 0)
		return (0);
	return (1);
}

t_pars	*map_part(int *iter, char **map, t_pars *ret)
{
	iter[1] = 0;
	if (iter[2] != 6)
		return (printf("error in map elements\n"), 
			ft_free_array(map), ft_free_textures(&ret), free(ret), NULL);
	while (map[iter[1]] && checker(map[iter[1]]) == 0)
		iter[1]++;
	if (parse_map(map + iter[1], &ret) == -1)
		return (ft_free_textures(&ret),
			free(ret), printf("error in map\n"), NULL);
	return (ft_free_array(map), ret);
}

t_pars	*ft_map_parser(char *file_name)
{
	char	**map;
	char	**txt;
	t_pars	*ret;
	int		iter[3];

	iter[0] = -1;
	iter[2] = 0;
	ret = allocate_struct();
	if (!ret)
		return (NULL);
	map = map_reader(file_name);
	txt = ft_split("NO SO WE EA F C", ' ');
	while (txt[++iter[0]])
	{
		iter[1] = -1;
		while (++iter[1] < ft_arr_len(map))
		{
			while (map[iter[1]] && ft_strncmp(map[iter[1]], "\n", 1) == 0)
				iter[1]++;
			if (skip_spaces_and_compare(map[iter[1]], txt[iter[0]]) == 0)
				iter[2] += check_type(txt[iter[0]], map[iter[1]], &ret);
		}
	}
	ft_free_array(txt);
	return (map_part(iter, map, ret));
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

int	parse_map(char **map, t_pars **data)
{
	int	longest_line;
	int	i;

	longest_line = ft_longest_line(map);
	if (longest_line == ERROR)
	{
		return (ERROR);
	}
	i = -1;
	while (map[++i])
		while ((int)ft_strlen(map[i]) < longest_line)
			map[i] = ft_strjoin(map[i], " ");
	if (check_for_tabs(map) == ERROR)
		return (ERROR);
	if (check_map(map) == -1)
		return (ERROR);
	if (get_player_direction(map) == -1)
		return (ERROR);
	(*data)->map.map = ft_allocate_clone(map);
	(*data)->map.height = ft_arr_len(map);
	(*data)->map.width = longest_line;
	return (1);
}
