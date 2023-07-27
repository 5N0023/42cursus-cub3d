/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:24:25 by mjarboua          #+#    #+#             */
/*   Updated: 2023/07/26 21:06:29 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_pars	*ft_map_parser(char *file_name)
{
	char	**map;
	t_pars	*ret;
	int		i;

	i = 0;
	ret = allocate_struct();
	if (!ret)
		return (NULL);
	map = map_reader(file_name);
	while (map[i] && ft_strncmp(map[i], "\n", 1) == 0)
		i++;
	if (texture_parser(map, &ret, &i) == ERROR)
		return (printf("error in textures\n"), ft_free_array(map), NULL);
	while (map[i] && ft_strncmp(map[i], "\n", 1) == 0)
		i++;
	if (color_parser(map, &ret, &i) == ERROR)
		return (printf("error in color\n"), ft_free_array(map), NULL);
	while (map[i] && ft_strncmp(map[i], "\n", 1) == 0)
		i++;
	if (parse_map(map + i, &ret) == ERROR)
		return (printf("error in map\n"), ft_free_array(map), NULL);
	return (ft_free_array(map), ret);
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
			map[i] = ft_strjoin(map[i], "*");
	if (check_for_tabs(map) == ERROR)
		return (ERROR);
	if (check_map(map) == -1)
		return (ERROR);
	(*data)->map.map = ft_allocate_clone(map);
	(*data)->map.height = ft_arr_len(map);
	(*data)->map.width = longest_line;
	return (1);
}
