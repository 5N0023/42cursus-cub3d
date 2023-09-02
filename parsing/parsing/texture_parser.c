/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:14:49 by mjarboua          #+#    #+#             */
/*   Updated: 2023/09/02 19:59:44 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"


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

void	ft_free_textures(t_pars **p)
{
	if ((*p)->north)
		free((*p)->north);
	if ((*p)->south)
		free((*p)->south);
	if ((*p)->east)
		free((*p)->east);
	if ((*p)->west)
		free((*p)->west);
}

int	texture(char *line, t_pars **ret)
{
	char	**split;
	int		fd;

	split = ft_split(line, ' ');
	if (ft_arr_len(split) != 2)
		return (ft_free_array(split), 1);
	fd = open(split[1], O_RDONLY);
	if (fd == -1)
		return (ft_free_array(split), 1);
	if (ft_strncmp(split[0], "NO", 2) == 0 && !(*ret)->north)
		(*ret)->north = ft_strdup(split[1]);
	if (ft_strncmp(split[0], "SO", 2) == 0 && !(*ret)->south)
		(*ret)->south = ft_strdup(split[1]);
	if (ft_strncmp(split[0], "WE", 2) == 0 && !(*ret)->west)
		(*ret)->west = ft_strdup(split[1]);
	if (ft_strncmp(split[0], "EA", 2) == 0 && !(*ret)->east)
		(*ret)->east = ft_strdup(split[1]);
	ft_free_array(split);
	return (1);
}

int	check_type(char *txt, char *line, t_pars **ret)
{
	int	r;

	r = 0;
	if (ft_strncmp(txt, "NO", 2) == 0)
		r = texture(line, ret);
	if (ft_strncmp(txt, "SO", 2) == 0)
		r = texture(line, ret);
	if (ft_strncmp(txt, "WE", 2) == 0)
		r = texture(line, ret);
	if (ft_strncmp(txt, "EA", 2) == 0)
		r = texture(line, ret);
	if (ft_strncmp(txt, "F", 1) == 0)
		r = color(line, ret);
	if (ft_strncmp(txt, "C", 1) == 0)
		r = color(line, ret);
	return (r);
}