/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:58:14 by mjarboua          #+#    #+#             */
/*   Updated: 2023/07/26 21:06:30 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

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
			if (map[i][j] == ' ')
				map[i][j] = '*';
			if (map[i][j] == '\t')
				return (-1);
		}
	}
	return (1);
}

int	check_map(char **map)
{
	int		i;
	int		j;
	char	**c;

	i = -1;
	c = allocate_clone(map);
	while (c[++i])
	{
		j = -1;
		while (c[i][++j])
		{
			if (c[i][j] == '*')
			{
				if (c[i][j + 1] && c[i][j + 1] != '1' && c[i][j + 1] != '*')
					return (ft_free_array(c), -1);
				else if (j > 0 && c[i][j - 1] && c[i][j - 1] != '1' && c[i][j - 1] != '*')
					return (ft_free_array(c), -1);
				else if (c[i + 1] && c[i + 1][j] != '1' && c[i + 1][j] != '*')
					return (ft_free_array(c), -1);
				else if (i > 0 && c[i - 1] && c[i - 1][j] && c[i - 1][j] != '1' && c[i - 1][j] != '*')
					return (ft_free_array(c), -1);
			}
		}
	}
	return (ft_free_array(c), 1);
}
