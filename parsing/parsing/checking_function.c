/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:58:14 by mjarboua          #+#    #+#             */
/*   Updated: 2023/09/06 15:59:44 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	not_map_element(char c)
{
	if (c != 'W' && c != 'S' &&c!= 'N' && c !='E' && c != '0' && c != '1'
		&& c != 'D' && c!= 'd' && c != ' ')
		return (1); 
	return (0);
}

int	check_for_tabs(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (not_map_element(map[i][j]) && map[i][j] != '\n')
				return (ERROR);
			if (map[i][j] == ' ')
				map[i][j] = '*';
			if (map[i][j] == '\n' && ft_strlen(map[i]) > 1)
				map[i][j] = '*';
			if (map[i][j] == '\t')
				return (ERROR);
		}
	}
	return (1);
}

int	check_player_surroundings(char **p, int i, int j)
{
	if (p[i][j + 1] == '*')
		return (-1);
	if (p[i][j - 1] == '*')
		return (-1);
	if (p[i + 1] && p[i + 1][j] == '*')
		return (-1);
	if (i > 0 && p[i - 1] && p[i - 1][j] == '*')
		return (-1);
	return (1);
}

int	check_aftermap(char **p, int i)
{
	int	f;
	int	j;

	f = -1;
	while (p[++f])
	{
		j = -1;
		while (p[f][++j])
		{
			if (p[f][j] == 'N' || p[f][j] == 'S'
				|| p[f][j] == 'W' || p[f][j] == 'E')
			{
				if (check_player_surroundings(p, f, j) == -1)
					return (ft_free_array(p), -1);
			}
		}
	}
	while (p[i])
	{
		if (ft_strncmp(p[i], "\n", 1) != 0)
			return (ft_free_array(p), -1);
		i++;
	}
	return (ft_free_array(p), 1);
}

int	check_map(char **p)
{
	int		i;
	int		j;

	i = -1;
	while (p[++i] && ft_strncmp(p[i], "\n", 1) != 0)
	{
		j = -1;
		while (p[i][++j])
		{
			if (p[i][j] == '*')
			{
				if (p[i][j + 1] && p[i][j + 1] != '1' && p[i][j + 1] != '*')
					return (ft_free_array(p), -1);
				else if (j > 0 && p[i][j - 1]
					&& p[i][j - 1] != '1' && p[i][j - 1] != '*')
					return (ft_free_array(p), -1);
				else if (p[i + 1] && p[i + 1][j] != '1' && p[i + 1][j] != '*')
					return (ft_free_array(p), -1);
				else if (i > 0 && p[i - 1] && p[i - 1][j]
					&& p[i - 1][j] != '1' && p[i - 1][j] != '*')
					return (ft_free_array(p), -1);
			}
		}
	}
	return (check_aftermap(p, i));
}
