/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:53:44 by mjarboua          #+#    #+#             */
/*   Updated: 2023/07/27 08:08:10 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// the stuct that is going to hold the info like textures on colors



struct				s_mapp
{
	char			**map;
	size_t			width;
	size_t			height;
};

struct				texture
{
	void			*img;
	int				*addr;
	int				bpp;
	int				line_length;
	int				endian;
	int				width;
	int				height;
};


typedef struct s_pars
{
	struct s_mapp	map;
	int				floorcolor;
	int				ceilingcolor;
	char			*south;
	char			*west;
	char			*east;
	char			*north;
}					t_pars;
#endif