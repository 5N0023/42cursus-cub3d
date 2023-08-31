/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:58:14 by mjarboua          #+#    #+#             */
/*   Updated: 2023/08/30 19:39:36 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	not_map_element(char c)
{
	if (c != 'W' && c != 'E' && c != 'N' && c != 'S' && c != '1' && c != '0' && c != ' ' && c != 'd' && c != 'D')
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
			if (not_map_element(map[i][j]))
				return (ERROR);
			if (map[i][j] == ' ')
				map[i][j] = '*';
			if (map[i][j] == '\t')
				return (ERROR);
		}
	}
	return (1);
}

int	check_map(char **p)
{
	int		i;
	int		j;

	i = -1;
	while (p[++i])
	{
		j = -1;
		while (p[i][++j])
		{
			if (p[i][j] == '*')
			{
				if (p[i][j + 1] && p[i][j + 1] != '1' && p[i][j + 1] != '*')
					return (-1);
				else if (j > 0 && p[i][j - 1]
					&& p[i][j - 1] != '1' && p[i][j - 1] != '*')
					return (-1);
				else if (p[i + 1] && p[i + 1][j] != '1' && p[i + 1][j] != '*')
					return (-1);
				else if (i > 0 && p[i - 1] && p[i - 1][j]
					&& p[i - 1][j] != '1' && p[i - 1][j] != '*')
					return (-1);
			}
		}
	}
	return (1);
}
