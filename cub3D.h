# ifndef CUB3D_H
# define CUB3D_H

# define SPEED 0.1
# define NORD 0
#define WINDOWW 1000
# define SUD 1
# define EAST 2
# define OUEST 3
# define VERTICALE 0
# define HORIZONTALE 1
# define NORMAL 0
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
# define CLOSED 1
# define OPENED 0
# define OPENING 2
# define CLOSING 3
# define NS 0
# define WE 1
# define TO_RAD  (M_PI / 180.0)
# include "MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_doorlist
{
	double			doorhitx;
	double			doorhity;
	int				doorhit;
	int 			doorhitside;
	double 			doordistance;
	struct s_doorlist *next;
} t_doorlist;


struct				s_ray
{
	double			x;
	int				windowx;
	double			y;
	double			angle;
	double			distance;
	double			dx;
	double			dy;
	int				hitside;
	int				texture;
	t_doorlist			*doorlist;
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

typedef struct s_doors
{
	int 			frame;
	int				state;
	int				x;
	int				y;
	int 			side;
} t_doors;



struct				s_gun
{
	struct s_normal	normal;
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
	t_doors			*doors;
	int 			doors_count;
	
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
	mlx_image_t	**door;
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
	double			angle;
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
void door_textures(t_data *data);
int door_state(t_data *data, int x, int y);
int get_door_frame(t_doorlist *tmp,t_data *data);
void door_frames_setter(t_data *data);
void door_frames_controller(t_data *data);
void add_back_to_doors(t_data *data, double x, double y,int side);
void sort_door_list(t_data *data, int reverse);
void free_door_list(t_data *data);
double	collision(double angle,t_data *data);
void	castrayvertical(t_hit *vhit, t_data *data);
void	castrayhorizontal(t_hit *hhit,t_data *data);
void draw_map(t_data *data, int size, int color);
mlx_t *initdefaultval(t_data *data_ptr);
void game(t_data *data);
void	move_player(t_data *data);
int ft_pixel(int r, int g, int b, int a);
mlx_keyfunc	key_hook(mlx_key_data_t key, t_data *data);
void normalize_angle(double *angle);
void put_mouse_sensitive(t_data *data,mlx_image_t *image);
void put_number_pos(mlx_image_t *image,mlx_image_t *img,int x,int y);
void put_player_speed(t_data *data,mlx_image_t *image);
void put_to_dataimg(t_data *data,mlx_image_t *image,int x,int y);
void render_door_WE(t_data *data,int x,double wallheight,t_doorlist *tmp);
void render_door_NS(t_data *data,int x,double wallheight,t_doorlist *tmp);

#include "parsing/includes/parsing.h"
#endif