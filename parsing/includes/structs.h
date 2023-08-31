/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:53:44 by mjarboua          #+#    #+#             */
/*   Updated: 2023/08/30 19:46:05 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// the stuct that is going to hold the info like textures on colors

enum e_grid
{
	X,
	Y
};

enum	e_side
{
	NORTH_T,
	SOUTH_T,
	EAST_T,
	WEST_T
};

enum e_iter
{
	I,
	J
};

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