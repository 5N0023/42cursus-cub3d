/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:24:25 by mjarboua          #+#    #+#             */
/*   Updated: 2023/09/06 15:40:36 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"
void	free_list(t_pars *p)
{
	if (!p)
		return ;
	if (p->east)
		free(p->east);
	if (p->west)
		free(p->west);
	if (p->south)
		free(p->south);
	if (p->north)
		free(p->north);
	ft_free_array(p->map.map);
	free(p);
}

int	skip_spaces_and_compare(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (1);
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (0);
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (0);
	if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		return (0);
	if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		return (0);
	if (line[i] == 'C' && line[i + 1] == ' ')
		return (0);
	if (line[i] == 'F' && line[i + 1] == ' ')
		return (0);
	return (1);
}

t_pars	*map_part(int *iter, char **map, t_pars *ret)
{
	iter[1] = 0;
	if (iter[2] != 6)
		return (printf("error in map elements\n"), free_list(ret), ft_free_array(map), NULL);
	while (map[iter[1]] && checker(map[iter[1]]) == 0)
		iter[1]++;
	if (parse_map(map + iter[1], &ret) == -1)
		return (free_list(ret), ft_free_array(map)
		, printf("error in map\n"), NULL);
	return (ft_free_array(map), ret);
}


t_pars	*ft_map_parser(char *file_name)
{
	char	**map;
	t_pars	*ret;
	int		iter[3];

	iter[0] = -1;
	iter[2] = 0;
	ret = allocate_struct();
	if (!ret)
		return (NULL);
	map = map_reader(file_name);
	while (map[++iter[0]])
	{
		while (map[iter[0]] && ft_strncmp(map[iter[0]], "\n", 1) == 0)
			iter[0]++;
		if (skip_spaces_and_compare(map[iter[0]]) == 0)
			iter[2] += check_type(map[iter[0]], &ret);
	}
	return (map_part(iter, map, ret));
}

char	**get_a_clone(char **p)
{
	char	**ret;
	int		i;

	i = -1;
	ret = malloc(sizeof(char *) * (ft_arr_len(p) + 3));
	if (!ret)
		return (NULL);
	ret[0] = ft_strdup("");
	while (++i < ft_longest_line(p))
		ret[0] = ft_strjoin(ret[0], "*");
	i = 1;
	while (p[i - 1])
	{
		ret[i] = ft_strdup(p[i - 1]);
		i++;
	}
	ret[i++] = ft_strdup(ret[0]);
	ret[i] = NULL;
	return (ret);
}

int	parse_map(char **map, t_pars **data)
{
	int	longest_line;
	int	i;

	longest_line = ft_longest_line(map);
	if (longest_line == ERROR)
		return (ERROR);
	i = -1;
	while (map[++i])
		while ((int)ft_strlen(map[i]) < longest_line)
			map[i] = ft_strjoin(map[i], " ");
	if (check_for_tabs(map) == ERROR)
		return (ERROR);
	if (check_map(get_a_clone(map)) == -1)
		return (ERROR);
	if (get_player_direction(map) == -1)
		return (ERROR);
	(*data)->map.map = ft_allocate_clone(map);
	(*data)->map.height = ft_arr_len(map);
	(*data)->map.width = longest_line;
	return (1);
}
