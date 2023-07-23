#ifndef CUB3D_H
# define CUB3D_H

# define SPEED 0.1
# define WINDOWW 1000
# define ROTATION 0.1
# define FOV 60
# define RAY 1000
# define NORD 0
# define SUD 1
# define EST 2
# define OUEST 3

# include "MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_ray
{
	double		x;
	double		y;
	double		angle;
	double		distance;
	double		dx;
	double		dy;
	int			hitside;
}				t_ray;

typedef struct s_player
{
	double		x;
	double		y;
	double		speed;
	double		rotation;
	double		angle;
	int			wpress;
	int			spress;
	int			dpress;
	int			apress;

}				t_player;

typedef struct s_map
{
	char		**map;
	size_t		width;
	size_t		height;
}				t_map;

typedef struct texture
{
	void		*img;
	int			*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_texture;

typedef struct s_data
{
	mlx_t		*mlx;
	void		*img;
	t_texture	*texture;
	t_map		*map;
	t_player	*player;
	t_ray		*ray;
	double		center;
	double		fov;
	int			floorcolor;
	int			ceilingcolor;
}				t_data;

#endif