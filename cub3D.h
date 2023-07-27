# ifndef CUB3D_H
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
# define NORMAL 0
# define VALORANT 1
# define CSGO 2
# define STARTSCREEN 0
# define STARTMENU 1
# define GAME 2
# define PAUSE 3
# define SHOOT 1
# define RELOAD 2
# define LOOK 3
# define START 4
# define EXIT 1
# define RESUME 2
# define OPTIONS 8
# define NONE 0

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
	double			sensitivity;
	mlx_image_t		*cursor;
}					t_mouse;

struct s_normal
{
	mlx_image_t		**gunshoot;
	mlx_image_t		**gunreload;
	mlx_image_t		**bullets;
	int 			bullet;
};
struct  s_valorant
{
	mlx_image_t		**gunshoot;
	mlx_image_t		**gunreload;
	int 			bullet;
};

struct s_csgo
{
	mlx_image_t		**gunshoot;
	mlx_image_t		**gunreload;
	int 			bullet;
};

struct				s_gun
{
	struct s_normal	normal;
	struct s_valorant valorant;
	struct s_csgo	csgo;
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
	char		*nord;
	char		*sud;
	char		*east;
	char		*ouest;
	mlx_image_t	*nordimg;
	mlx_image_t	*sudimg;
	mlx_image_t	*eastimg;
	mlx_image_t	*ouestimg;
};

struct				s_loading
{
	mlx_image_t		**frames;
};

struct				s_startmenu
{
	mlx_image_t		*frames;
	int 			button;
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
	struct s_loading loading;
	double			center;
	double			fov;
	int				floorcolor;
	int				ceilingcolor;
	int				state;
	int 			gamemode;
}					t_data;


void load_normal_texture(t_data *data);
unsigned int get_pixel(mlx_image_t *img,int i,int j);
void draw_gun_normal(t_data *data);
double	hits(double angle,t_data *data);
void startscreen(t_data *data);
void load_loading_texture(t_data *data);
void startmenu(t_data *data);
void load_startmenu_texture(t_data *data);
void draw_cursor(t_data *data);
void options(t_data *data);
void load_cursor(t_data *data);
void render_texture(t_data *data,int x,double wallheight);
void load_walls_textures(t_data *data);
#include "parsing/includes/parsing.h"
#endif