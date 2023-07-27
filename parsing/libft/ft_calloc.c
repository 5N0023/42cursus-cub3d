/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:56:58 by mjarboua          #+#    #+#             */
/*   Updated: 2023/07/20 12:11:54 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"


void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if ((SIZE_MAX <= count || SIZE_MAX == size)
		|| SIZE_MAX == (count * size))
		return (NULL);
	str = malloc(count * size);
	if (str == 0)
		return (str);
	ft_bzero(str, count * size);
	return (str);
}
