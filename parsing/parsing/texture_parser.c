/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:14:49 by mjarboua          #+#    #+#             */
/*   Updated: 2023/07/26 21:06:29 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	parse_texture(char *txt)
{
	int	fd;
	int	i;

	i = 0;
	while (txt[i] && txt[i] == ' ')
		i++;
	while (txt[i] && txt[i] != ' ')
		i++;
	while (txt[i] && txt[i] == ' ')
		i++;
	printf("%s the filename\n", txt + i);
	fd = open(txt + i, O_RDWR);
	if (fd == -1)
		return (perror("open"), -1);
	else
		return (close(fd), SUCCESS);
}

void	_replace(char *str)
{
	if (!str)
		return ;
	if (str[ft_strlen(str) - 1] == '\n' && ft_strlen(str) > 1)
		str[ft_strlen(str) - 1] = 0;
}

int	texture_parser(char **map, t_pars **data, int *i)
{
	if (check_texture(map, data, i) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
