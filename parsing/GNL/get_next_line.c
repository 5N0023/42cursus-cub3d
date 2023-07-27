/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:48:53 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/17 17:19:17 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*to_print(char *str)
{
	int		i;
	char	*s;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		s = ft_substr(str, 0, i + 1);
	if (str[i] == '\0')
		s = ft_strdup(str);
	if (!s)
		return (NULL);
	return (s);
}

char	*to_save(char *save)
{
	int		i;
	char	*s;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\0')
		return (free(save), NULL);
	i++;
	s = ft_strdup(save + i);
	if (!s)
		return (NULL);
	return (free(save), s);
}

char	*reeed(int fd, char *line)
{
	char	*reader;
	int		i;

	i = 1;
	reader = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!reader)
		return (NULL);
	while (i)
	{
		i = read(fd, reader, BUFFER_SIZE);
		if (i == -1)
			return (free(line), free(reader), NULL);
		reader[i] = '\0';
		line = ft_strjoin(line, reader);
		if (ft_strlen_mod(line, 1) == 1)
			break ;
	}
	return (free(reader), line);
}

char	*get_next_line(int fd)
{
	char		*ret;
	static char	*bucket;

	if (fd >= 0 && BUFFER_SIZE > 0)
	{
		bucket = reeed(fd, bucket);
		if (!bucket)
			return (NULL);
		ret = to_print(bucket);
		bucket = to_save(bucket);
	}
	else
		ret = NULL;
	return (ret);
}
