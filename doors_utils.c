/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 23:12:45 by mlektaib          #+#    #+#             */
/*   Updated: 2023/09/04 23:20:24 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	reverse_door_list(t_data *data)
{
	t_doorlist	*prev;
	t_doorlist	*current;
	t_doorlist	*next;

	prev = NULL;
	current = data->ray.doorlist;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	data->ray.doorlist = prev;
}

size_t	door_list_size(t_doorlist *head)
{
	size_t		size;
	t_doorlist	*tmp;

	size = 0;
	tmp = head;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

void	array_bubble_sort(t_doorlist **arr, size_t size)
{
	size_t	j;
	size_t	k;

	j = 0;
	while (j < size - 1)
	{
		k = 0;
		while (k < size - j - 1)
		{
			if (arr[k]->doordistance > arr[k + 1]->doordistance)
				swap(arr[k], arr[k + 1]);
			k++;
		}
		j++;
	}
}

void	rebuild_door_list(t_data *data, t_doorlist **arr, size_t size)
{
	size_t	i;

	i = 0;
	data->ray.doorlist = arr[0];
	while (i < size - 1)
	{
		arr[i]->next = arr[i + 1];
		i++;
	}
	arr[i]->next = NULL;
}

void	sort_door_list(t_data *data, int reverse)
{
	t_doorlist	*tmp;
	t_doorlist	**arr;
	size_t		size;
	size_t		i;

	size = door_list_size(data->ray.doorlist);
	if (size <= 1)
		return ;
	arr = malloc(sizeof(t_doorlist *) * size);
	tmp = data->ray.doorlist;
	i = 0;
	while (tmp)
	{
		arr[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	array_bubble_sort(arr, size);
	rebuild_door_list(data, arr, size);
	if (reverse)
		reverse_door_list(data);
	free(arr);
}
