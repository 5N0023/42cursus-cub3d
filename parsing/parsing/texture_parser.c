/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:14:49 by mjarboua          #+#    #+#             */
/*   Updated: 2023/09/06 15:35:46 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	checker(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_strncmp(line + i, "WE", ft_strlen("WE")) == 0)
		return (0);
	if (ft_strncmp(line + i, "EA", ft_strlen("EA")) == 0)
		return (0);
	if (ft_strncmp(line + i, "SO", ft_strlen("SO")) == 0)
		return (0);
	if (ft_strncmp(line + i, "NO", ft_strlen("NO")) == 0)
		return (0);
	if (ft_strncmp(line + i, "F", ft_strlen("F")) == 0)
		return (0);
	if (ft_strncmp(line + i, "C", ft_strlen("C")) == 0)
		return (0);
	if (ft_strncmp(line + i, "\n", ft_strlen("\n")) == 0)
		return (0);
	return (1);
}

void	_replace(char *str)
{
	if (!str)
		return ;
	if (str[ft_strlen(str) - 1] == '\n' && ft_strlen(str) > 1)
		str[ft_strlen(str) - 1] = 0;
}



int	texture(char *line, t_pars **ret)
{
	int		fd;
	int		i;
	char	*tmp;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	tmp = ft_strdup(line + i);
	i += 2;
	while (line[i] && line[i] == ' ')
		i++;
	fd = open(line + i, O_RDONLY);
	if (fd == -1)
		return (free(tmp), 1);
	if (ft_strncmp(tmp, "NO", 2) == 0 && !(*ret)->north)
		return ((*ret)->north = ft_strdup(line + i), free(tmp), 1);
	if (ft_strncmp(tmp, "SO", 2) == 0 && !(*ret)->south)
		return ((*ret)->south = ft_strdup(line + i), free(tmp), 1);
	if (ft_strncmp(tmp, "WE", 2) == 0 && !(*ret)->west)
		return ((*ret)->west = ft_strdup(line + i), free(tmp), 1);
	if (ft_strncmp(tmp, "EA", 2) == 0 && !(*ret)->east)
		return ((*ret)->east = ft_strdup(line + i), free(tmp), 1);
	return (1);
}

int	check_type(char *line, t_pars **ret)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		r = texture(line, ret);
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		r = texture(line, ret);
	if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		r = texture(line, ret);
	if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		r = texture(line, ret);
	if (line[i] == 'C' && line[i + 1] == ' ')
		r = color(line, ret);
	if (line[i] == 'F' && line[i + 1] == ' ')
		r = color(line, ret);
	return (r);
}
