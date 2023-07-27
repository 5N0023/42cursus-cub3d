/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:43:46 by mjarboua          #+#    #+#             */
/*   Updated: 2023/07/20 12:10:23 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	count_number(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*alloc(char *str, size_t num, size_t t)
{
	while (num > 0)
	{
		str[t--] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	size_t		num;
	size_t		t;
	char		*str;

	num = n;
	t = count_number(n);
	str = malloc((t + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[t--] = '\0';
	if (num == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	str = alloc(str, num, t);
	return (str);
}
