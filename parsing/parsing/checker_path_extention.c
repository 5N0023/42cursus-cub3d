/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_path_extention.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:32:44 by mjarboua          #+#    #+#             */
/*   Updated: 2023/07/26 21:06:29 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	check_file_extention(char *file)
{
	int	i;

	i = ft_strlen(file) - 4;
	if (ft_strncmp(file + i, EXTENTION, 4))
		return (ERROR);
	if (access(file, F_OK) || access(file, R_OK))
		return (ERROR);
	return (SUCCESS);
}
