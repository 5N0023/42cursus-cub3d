/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:13:56 by mjarboua          #+#    #+#             */
/*   Updated: 2023/08/21 22:06:28 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

int	ft_strlen_mod(char *str, int flag)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	else if (flag == 0)
	{
		while (str[i])
			i++;
		return (i);
	}
	else
	{
		while (str[i])
		{
			if (str[i] == '\n')
				return (1);
			i++;
		}
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	c;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	str = malloc((ft_strlen_mod(s1, 0)
				+ ft_strlen_mod(s2, 0) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	c = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[c] != '\0')
		str[i++] = s2[c++];
	str[i] = '\0';
	return (free(s1), str);
}

// char	*ft_substr(char *s, int start, int len)
// {
// 	int		j;
// 	char	*str;

// 	if (!s)
// 		return (NULL);
// 	if (ft_strlen_mod(s, 0) == 0 || len <= 0)
// 		return (ft_strdup(""));
// 	if (start > ft_strlen_mod(s, 0))
// 		return (ft_strdup(""));
// 	if (len > ft_strlen_mod(s, 0 + start))
// 		len = ft_strlen_mod(s, 0 + start);
// 	str = malloc((len + 1) * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	j = 0;
// 	while (j < len && s[start])
// 	{
// 		str[j++] = s[start++];
// 	}
// 	str[j] = '\0';
// 	return (str);
// }
