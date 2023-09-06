/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:07:12 by mjarboua          #+#    #+#             */
/*   Updated: 2023/09/04 23:37:09 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	ft_pixel(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static int	ft_fill_int(char *arr)
{
	char		**c;
	int			i;
	int			j;
	int			ret;

	i = 0;
	ret = 0;
	c = ft_split(arr, ',');
	if (ft_arr_len(c) != 3)
		return (ft_free_array(c), ERROR);
	while (c[i])
	{
		j = 0;
		while (c[i][j])
		{
			if (c[i][j] != '\n' && ft_isdigit(c[i][j]) == 0)
				return (ft_free_array(c), ERROR);
			j++;
		}
		if (ft_atoi(c[i]) == -1 || ft_atoi(c[i]) > 255 || ft_atoi(c[i]) < 0)
			return (ft_free_array(c), ERROR);
		i++;
	}
	ret = ft_pixel(ft_atoi(c[0]), ft_atoi(c[1]), ft_atoi(c[2]), 255);
	return (ft_free_array(c), ret);
}

int	parse_color(char *color)
{
	char	**_color;
	int		v;
	int		i;
	int		ret;

	i = 0;
	v = 0;
	ret = 0;
	_color = ft_split(color, ' ');
	if (_color[2])
		return (ft_free_array(_color), ERROR);
	while (_color[1][++i])
	{
		if (_color[1][i] == ',')
			v++;
	}
	if (v != 2)
		return (ft_free_array(_color), ERROR);
	ret = ft_fill_int(_color[1]);
	if (ret == -1)
		return (ft_free_array(_color), ERROR);
	return (ft_free_array(_color), ret);
}

int	color(char *line, t_pars **ret)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_strncmp(line + i, "F", 1) == 0 && (*ret)->floorcolor == -1)
	{
		(*ret)->floorcolor = parse_color(line);
		if ((*ret)->floorcolor == ERROR)
			return (0);
		else
			return (1);
	}
	if (ft_strncmp(line + i, "C", 1) == 0 && (*ret)->ceilingcolor == -1)
	{
		(*ret)->ceilingcolor = parse_color(line);
		if ((*ret)->ceilingcolor == ERROR)
			return (0);
		else
			return (1);
	}
	return (1);
}
