/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:12:47 by mjarboua          #+#    #+#             */
/*   Updated: 2023/07/20 12:11:54 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"


char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	if (len <= 0)
		return (0);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (((haystack[i + j] == needle[j])
				&& haystack[i + j]) && i + j < len)
		{
			if (((haystack[i + j] == needle[j]) && haystack[i + j]) && i == len)
				return (NULL);
			if (needle[j + 1] == '\0')
				return (&((char *)haystack)[i]);
			j++;
		}
		i++;
	}
	return (0);
}
