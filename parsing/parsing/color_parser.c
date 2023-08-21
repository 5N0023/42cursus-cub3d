/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:07:12 by mjarboua          #+#    #+#             */
/*   Updated: 2023/08/20 21:09:08 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	ft_pixel(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	ft_fill_int(char *arr)
{
	char		**c;
	int			i;
	int			j;
	int			ret;

	i = 0;
	ret = 0;
	c = ft_split(arr, ',');
	if (ft_arr_len(c) != 3)
		return (ERROR);
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
	ret = ft_pixel(ft_atoi(c[0]), ft_atoi(c[1]), ft_atoi(c[2]), 0xFF);
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
		(_color[1][i] == ',') && v++;
	if (v != 2)
		return (ERROR);
	ret = ft_fill_int(_color[1]);
	if (ret == -1)
		return (ft_free_array(_color), ERROR);
	return (ft_free_array(_color), ret);
}
