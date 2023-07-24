#ifndef CUB3D_H
# define CUB3D_H

# define SPEED 0.1
# define WINDOWW 1000
# define ROTATION 0.1
# define FOV 60
# define RAY 1000
# define NORD 0
# define SUD 1
# define EAST 2
# define OUEST 3
# define VERTICALE 0
# define HORIZONTALE 1

# include "MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

struct				s_ray
{
	double			x;
	double			y;
	double			angle;
	double			distance;
	double			dx;
	double			dy;
	int				hitside;
	int				texture;
};

struct				s_mouse
{
	int				x;
	int				y;
	int				oldx;
	int				oldy;
	int				click;
	int				anglemove;
	int				centermove;
}					t_mouse;

struct				s_gun
{
	mlx_image_t		*gun;
	mlx_image_t		*gunshoot;
	mlx_image_t		*gunreload[100];
	int				state;
};

struct				s_player
{
	double			x;
	double			y;
	double			speed;
	double			rotation;
	double			angle;
	int				wpress;
	int				spress;
	int				dpress;
	int				apress;
	struct s_gun	gun;
};

struct				s_map
{
	char			**map;
	size_t			width;
	size_t			height;
};

struct				s_texture
{
	mlx_image_t		*nord;
	mlx_image_t		*sud;
	mlx_image_t		*est;
	mlx_image_t		*ouest;
};

typedef struct s_hit
{
	double			x;
	double			xray;
	double			yray;
	double 			y;
	double			dx;
	double			dy;
	double			hitx;
	double			hity;
	int				hit;
	double			distance;
}					t_hit;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	struct s_player	player;
	struct s_map	map;
	struct s_ray	ray;
	struct s_mouse	mouse;
	struct s_texture texture;
	double			center;
	double			fov;
	int				floorcolor;
	int				ceilingcolor;
}					t_data;

#endif