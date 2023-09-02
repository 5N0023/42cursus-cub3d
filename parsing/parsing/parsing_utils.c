/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:09:32 by mjarboua          #+#    #+#             */
/*   Updated: 2023/09/02 20:04:59 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	get_map_len(char *file_name)
{
	int		i;
	int		fd;
	char	*buffer;

	i = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (printf("error in opening '%s'\n", file_name), exit(1), 1);
	buffer = get_next_line(fd);
	while (buffer)
	{
		i++;
		free(buffer);
		buffer = get_next_line(fd);
	}
	close(fd);
	return (i);
}

int	ft_longest_line(char **arr)
{
	int	i;
	int	line_length;

	i = 0;
	if (!arr[0])
		return (-1);
	line_length = ft_strlen(arr[0]);
	while (arr[i])
	{
		if (ft_strlen(arr[i]) > (size_t)line_length)
			line_length = ft_strlen(arr[i]);
		if (ft_strncmp(arr[i], "\n", 1) == 0 && i != ft_arr_len(arr)
			&& arr[i + 1] && ft_strncmp(arr[i + 1], "\n", 1))
			return (-1);
		i++;
	}
	return (line_length);
}

t_pars	*allocate_struct(void)
{
	t_pars	*ret;

	ret = malloc(sizeof(t_pars));
	if (!ret)
		return (NULL);
	ret->ceilingcolor = -1;
	ret->floorcolor = -1;
	ret->west = NULL;
	ret->east = NULL;
	ret->north = NULL;
	ret->south = NULL;
	ret->map.map = NULL;
	return (ret);
}

char	**ft_allocate_clone(char **original)
{
	int		i;
	char	**map;

	map = malloc(sizeof(char *) * (ft_arr_len(original) + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (original[i])
	{
		map[i] = ft_strdup(original[i]);
		i++;
	}
	map[i] = NULL;
	return (map);
}

char	**allocate_clone(char **v)
{
	int		i;
	int		j;
	char	**str;
	int		l;

	i = -1;
	str = malloc(sizeof(char *) * (ft_arr_len(v) + 3));
	l = ft_longest_line(v);
	while (++i < l)
		str[0] = ft_strjoin(str[0], "*");
	i = 1;
	j = 0;
	while (v[j])
		str[i++] = ft_strdup(v[j++]);
	j = i;
	i = -1;
	while (++i < l)
		str[j] = ft_strjoin(str[j], "*");
	j++;
	str[j] = NULL;
	return (str);
}
