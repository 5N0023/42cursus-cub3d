/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:25:11 by mjarboua          #+#    #+#             */
/*   Updated: 2023/09/04 23:36:56 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	put_texture_in_place(char *texture, char **target, t_pars **data)
{
	_replace(target[1]);
	if (target[2])
		return (-5);
	if (ft_strncmp(texture, "SO", 2) == 0 && !(*data)->south)
		(*data)->south = ft_strdup(target[1]);
	if (ft_strncmp(texture, "WE", 2) == 0 && !(*data)->west)
		(*data)->west = ft_strdup(target[1]);
	if (ft_strncmp(texture, "EA", 2) == 0 && !(*data)->east)
		(*data)->east = ft_strdup(target[1]);
	if (ft_strncmp(texture, "NO", 2) == 0 && !(*data)->north)
		(*data)->north = ft_strdup(target[1]);
	return (1);
}

int	check_texture(char **map, t_pars **data, int *i)
{
	int		counter;
	int		j;
	char	**arr;
	char	**txt;

	counter = 0;
	txt = ft_split("EA SO NO WE", ' ');
	while (map[*i])
	{
		j = -1;
		if (ft_strncmp(map[*i], "\n", 1) == 0)
			break ;
		while (txt[++j])
		{
			arr = ft_split(map[*i], ' ');
			if (ft_strncmp(txt[j], arr[0], ft_strlen(map[*i])) == 0
				&& arr[2] == NULL)
				counter += put_texture_in_place(txt[j], arr, data);
			ft_free_array(arr);
		}
		(*i)++;
	}
	if (counter != 4)
		return (ft_free_array(txt), ERROR);
	return (ft_free_array(txt), SUCCESS);
}

int	color_filler(char *color, t_pars **data)
{
	char	**arr;

	arr = ft_split(color, ' ');
	if (arr[2])
		return (ft_free_array(arr), -5);
	if (ft_strncmp("F", arr[0], ft_strlen(arr[0])) == 0)
	{
		(*data)->floorcolor = parse_color(color);
		if ((*data)->floorcolor == -1)
			return (ft_free_array(arr), -1);
	}
	if (ft_strncmp("C", arr[0], ft_strlen(arr[0])) == 0)
	{
		(*data)->ceilingcolor = parse_color(color);
		if ((*data)->ceilingcolor == -1)
			return (ft_free_array(arr), -1);
	}
	return (ft_free_array(arr), 1);
}

int	color_parser(char **map, t_pars **data, int *i)
{
	int		counter;
	int		j;
	char	**arr;
	char	**txt;

	counter = 0;
	txt = ft_split("F C", ' ');
	while (map[*i])
	{
		j = -1;
		if (ft_strncmp(map[*i], "\n", 1) == 0)
			break ;
		while (txt[++j])
		{
			arr = ft_split(map[*i], ' ');
			if (ft_strncmp(txt[j], arr[0], ft_strlen(map[*i])) == 0)
				counter += color_filler(map[*i], data);
			ft_free_array(arr);
		}
		(*i)++;
	}
	if (counter != 2)
		return (ft_free_array(txt), ERROR);
	return (ft_free_array(txt), SUCCESS);
}
