/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:26:04 by mjarboua          #+#    #+#             */
/*   Updated: 2023/08/18 13:04:11 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(char *str1, char *str2, size_t n)
{
	if (!str1)
		return (0);
	if (!str2)
		return (0);
	while (n && *str1 && *str2 && (*str1 == *str2))
	{
		str1++;
		str2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*str1 - *str2);
}
