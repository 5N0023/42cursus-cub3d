/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:14:49 by mjarboua          #+#    #+#             */
/*   Updated: 2023/08/30 19:41:30 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"


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

int	texture_parser(char **map, t_pars **data, int *i)
{
	if (check_texture(map, data, i) == ERROR)
		return (ft_free_textures(data), ERROR);

	return (SUCCESS);
}

