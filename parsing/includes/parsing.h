/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:19:18 by mjarboua          #+#    #+#             */
/*   Updated: 2023/07/26 21:03:55 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define ERROR -1
# define SUCCESS 1

# define EXTENTION ".cub"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "structs.h"
# include "libft.h"
# include "get_next_line.h"
#include "../../cub3D.h"

// util functions
int		get_map_len(char *file_name);
void	_replace(char *str);
int		ft_longest_line(char **arr);
int		check_for_tabs(char **map);
char	**allocate_clone(char **v);
char	**ft_allocate_clone(char **original);
char	**allocate_clone(char **v);
t_pars	*allocate_struct(void);

//parsing functions
int     parser(int c, char **v, t_data *data);
int	checker(char *line);
int	check_type(char *line, t_pars **ret);
int		parse_color(char *color);
int	color(char *line, t_pars **ret);
int		parse_texture(char *txt);
int		texture_parser(char **map, t_pars **data, int *i);
int		check_file_extention(char *file);
int		put_texture_in_place(char *texture, char **target, t_pars **data);
int		check_texture(char **map, t_pars **data, int *i);
int		color_filler(char *color, t_pars **data);
int		color_parser(char	**map, t_pars **data, int *i);
int		parse_map(char **map, t_pars **data);
int		check_map(char **map);
char	**map_reader(char *file_name);
t_pars	*ft_map_parser(char *file_name);
void	ft_free_textures(t_pars **p);
int			get_player_direction(char **m);

#endif
