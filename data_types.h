/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:11:21 by mlektaib          #+#    #+#             */
/*   Updated: 2023/09/04 20:12:35 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_TYPES_H
# define DATA_TYPES_H

typedef struct s_doorlist
{
	double				doorhitx;
	double				doorhity;
	int					doorhit;
	int					doorhitside;
	double				doordistance;
	struct s_doorlist	*next;
}						t_doorlist;

struct					s_ray
{
	double				x;
	int					windowx;
	double				y;
	double				angle;
	double				distance;
	double				dx;
	double				dy;
	int					hitside;
	int					texture;
	t_doorlist			*doorlist;
};

struct					s_mouse
{
	int					x;
	int					y;
	int					oldx;
	int					oldy;
	int					click;
	int					anglemove;
	int					centermove;
	double				sensitivity;
	mlx_image_t			*cursor;
}						t_mouse;

struct					s_normal
{
	mlx_image_t			**gunshoot;
	mlx_image_t			**gunreload;
	mlx_image_t			**bullets;
	int					bullet;
};

typedef struct s_doors
{
	int					frame;
	int					state;
	int					x;
	int					y;
	int					side;
}						t_doors;

struct					s_gun
{
	struct s_normal		normal;
	int					state;
};

struct					s_player
{
	double				x;
	double				y;
	double				speed;
	double				rotation;
	double				angle;
	int					wpress;
	int					spress;
	int					dpress;
	int					apress;
	struct s_gun		gun;
};

struct					s_map
{
	char				**map;
	size_t				width;
	size_t				height;
	t_doors				*doors;
	int					doors_count;
};

struct					s_texture
{
	char				*nord;
	char				*sud;
	char				*east;
	char				*ouest;
	mlx_image_t			*nordimg;
	mlx_image_t			*sudimg;
	mlx_image_t			*eastimg;
	mlx_image_t			*ouestimg;
	mlx_image_t			**door;
};

struct					s_loading
{
	mlx_image_t			**frames;
};

struct					s_startmenu
{
	mlx_image_t			*frames;
	int					button;
};

typedef struct s_hit
{
	double				x;
	double				xray;
	double				yray;
	double				y;
	double				dx;
	double				dy;
	double				hitx;
	double				hity;
	int					hit;
	double				distance;
	double				angle;
}						t_hit;

typedef struct s_data
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	struct s_player		player;
	struct s_map		map;
	struct s_ray		ray;
	struct s_mouse		mouse;
	struct s_texture	texture;
	struct s_loading	loading;
	double				center;
	double				fov;
	int					floorcolor;
	int					ceilingcolor;
	int					state;
	int					gamemode;
}						t_data;

#endif