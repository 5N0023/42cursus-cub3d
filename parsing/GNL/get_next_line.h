/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 21:13:28 by mjarboua          #+#    #+#             */
/*   Updated: 2023/08/24 19:47:21 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 11
# endif

int		ft_strlen_mod(char *str, int flag);
char	*ft_strjoin(char *s1, char *s2);
char	*_ft_strjoin(char *s1, char *s2);
char	*reeeed(int fd, char *bucket);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdup(char *s1);
char	*get_next_line(int fd);

#endif