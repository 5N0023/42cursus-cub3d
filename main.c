#include "cub3D.h"
#include <signal.h>




float color_distance(unsigned char r1, unsigned char g1, unsigned char b1, unsigned char a1,
                     unsigned char r2, unsigned char g2, unsigned char b2, unsigned char a2) {
    return sqrtf(powf(r1 - r2, 2) + powf(g1 - g2, 2) + powf(b1 - b2, 2) + powf(a1 - a2, 2));
}

int ft_pixel(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
unsigned int get_pixel(mlx_image_t *img,int i,int j)
{
	int pixel;
	uint8_t r;
	uint8_t b;
	uint8_t g;
	uint8_t a;
	int pos = (j * 4 * img->width) + i * 4;
	r = img->pixels[pos];
	g = img->pixels[pos+1];
	b = img->pixels[pos+2];
	a = img->pixels[pos+3];
	return(ft_pixel(r,g,b,a));
}



void draw_map(t_data *data, int x, int y, int size, int color)
{
	size = 20;
    int playerX = (int)data->player.x;
    int playerY = (int)data->player.y;
    int halfRange = 5; 

    for (int i = playerY - halfRange; i <= playerY + halfRange; i++)
    {
        for (int j = playerX - halfRange; j <= playerX + halfRange; j++)
        {
            if (i >= 0 && j >= 0 && j < data->map.width && i < data->map.height)
            {
				if(data->map.map[i][j] == '0')
					color = 0x2E3357FF;
                else
					color = 0x1A0E13FF;
                for (int k = 0; k < size; k++)
                {
                    for (int l = 0; l < size; l++)
                    {
                        int drawX = (j - (playerX - halfRange)) * size + l;
                        int drawY = (i - (playerY - halfRange)) * size + k;
                        mlx_put_pixel(data->img, drawX, drawY, color);
                    }
                }
			}
			else {
				color = 0x1A0E13FF;
				for (int k = 0; k < size; k++)
                {
                    for (int l = 0; l < size; l++)
                    {
                        int drawX = (j - (playerX - halfRange)) * size + l;
                        int drawY = (i - (playerY - halfRange)) * size + k;
                        mlx_put_pixel(data->img, drawX, drawY, color);
                    }
                }

            }
        }
    }
	x = halfRange * size + ((size - 8)/2);
	y = halfRange * size  + ((size - 8)/2);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			mlx_put_pixel(data->img, x + j, y + i, 0xFF0000FF);
}

void	draw_line(int x0, int y0, int x1, int y1, int color, t_data *data)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	k;
	int	e2;

	if (y0 < 0)
		y0 = 0;
	if (y0 >= WINDOWW)
		y0 = WINDOWW - 1;
	if (y1 < 0)
		y1 = 0;
	if (x0 < 0)
		x0 = 0;
	if (y1 >= WINDOWW)
		y1 = WINDOWW - 1;
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx - dy;
	k = 0;
	while (1)
	{
		if(x0 >= 0 && x0 < WINDOWW && y0 >= 0 && y0 < WINDOWW)
			mlx_put_pixel(data->img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
		k++;
	}
}


void	move_player(t_data *data)
{

	double	distance1;
	double	distance2;
	while (data->player.angle >= 360)
		data->player.angle -= 360;
	while (data->player.angle < 0)
		data->player.angle += 360;

	if (data->player.spress)
	{
		distance1 = hits(data->player.angle + 10 + 180,data);
		distance2 = hits(data->player.angle - 10 + 180,data);
		if (distance1 > 0.2 && distance2 > 0.2)
		{
			data->player.x += cosf((data->player.angle + 90) * M_PI / 180.0) * data->player.speed;
			data->player.y -= sinf((data->player.angle + 90) * M_PI / 180.0) * data->player.speed;
		}
	}
	if (data->player.wpress)
	{
		distance1 = hits(data->player.angle + 10, data);
		distance2 = hits(data->player.angle - 10,data);
		if (distance1 > 0.2 && distance2 > 0.2)
		{
			data->player.x -= cosf((data->player.angle + 90) * M_PI / 180.0) * data->player.speed;
			data->player.y += sinf((data->player.angle + 90) * M_PI / 180.0) * data->player.speed;
		}
	}
	if (data->player.dpress)
	{
		distance1 = hits(data->player.angle + 10 - 90,data);
		distance2 = hits(data->player.angle - 10 - 90,data);
		if (distance1 > 0.2 && distance2 > 0.2)
		{
			data->player.x -= cosf((data->player.angle)*M_PI / 180.0) * data->player.speed;
			data->player.y += sinf((data->player.angle)*M_PI / 180.0) * data->player.speed;
		}
	}
	if (data->player.apress)
	{
		distance1 = hits(data->player.angle + 10 + 90,data);
		distance2 = hits(data->player.angle - 10 + 90,data);
		if (distance1 > 0.2 && distance2 > 0.2)
		{
			data->player.x += cosf((data->player.angle)*M_PI / 180.0) * data->player.speed;
			data->player.y -= sinf((data->player.angle)*M_PI / 180.0) * data->player.speed;
		}
	}
	if(data->mouse.oldx != data->mouse.x)
			data->player.angle = (data->mouse.x * -data->mouse.sensitivity);
    data->center  = WINDOWW / 2 + data->mouse.y * -data->mouse.sensitivity;
	if(data->center <= -500)
	{
		data->center = -500;
		mlx_set_mouse_pos(data->mlx,data->mouse.x, data->mouse.y);
	}
	if(data->center >= WINDOWW + 500)
	{

		data->center = WINDOWW + 500;
		mlx_set_mouse_pos(data->mlx, data->mouse.x, data->mouse.y);
	}
	if(data->mouse.click == 1 && data->player.gun.state == 0)
		data->player.gun.state = SHOOT;
	data->mouse.oldx = data->mouse.x;
	data->mouse.oldy = data->mouse.y;
	while (data->player.angle >= 360)
		data->player.angle -= 360;
	while (data->player.angle < 0)
		data->player.angle += 360;
}

mlx_keyfunc	key_hook(mlx_key_data_t key, t_data *data)
{
	double	x;
	double	y;
	double	distance1;
	double	distance2;

	x = data->player.x;
	y = data->player.y;
	if (key.key == MLX_KEY_ESCAPE)
		exit(0);
	if (key.key == MLX_KEY_RIGHT)
		data->player.angle -= 2;
	if (key.key == MLX_KEY_LEFT)
		data->player.angle += 2;
	if (key.key == MLX_KEY_S && key.action == MLX_PRESS)
		data->player.spress = 1;
	if (key.key == MLX_KEY_S && key.action == MLX_RELEASE)
		data->player.spress = 0;
	if (key.key == MLX_KEY_W && key.action == MLX_PRESS)
		data->player.wpress = 1;
	if (key.key == MLX_KEY_W && key.action == MLX_RELEASE)
		data->player.wpress = 0;
	if (key.key == MLX_KEY_D && key.action == MLX_PRESS)
		data->player.dpress = 1;
	if (key.key == MLX_KEY_D && key.action == MLX_RELEASE)
		data->player.dpress = 0;
	if (key.key == MLX_KEY_A && key.action == MLX_PRESS)
		data->player.apress = 1;
	if (key.key == MLX_KEY_A && key.action == MLX_RELEASE)
		data->player.apress = 0;
	if (key.key == MLX_KEY_R && key.action == MLX_PRESS)
		data->player.gun.state = RELOAD;
	if (key.key == MLX_KEY_P && key.action == MLX_PRESS && (data->gamemode == GAME || data->gamemode == STARTMENU))
	{
		if(data->gamemode == STARTMENU)
		{
			data->gamemode = GAME;
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
		}
		else
			{mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
			data->gamemode = STARTMENU;}
	}
	return (NULL);
}

mlx_mousefunc	key_mouse(mouse_key_t button, action_t action,
		modifier_key_t modifier_key, t_data *data)
{
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		data->mouse.click = 1;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		data->mouse.click = 0;
	return (NULL);
}
mlx_cursorfunc	key_cursor(double x, double y, t_data *data)
{
	if(data->gamemode == GAME)
	{data->mouse.x = x;
	data->mouse.y = y;}
	return (NULL);
}

void drawpixels(t_data *data, int k, double draw, double wallheight)
{

	
}
void game(t_data *data)
{
	double	POV;
	double	angle;
	double	draw;
	int		k;
	double	a;
	double	distance;
	double	wallheight;
	int		color;
	move_player(data);	
	
	POV = 60;
	for (int i = 0; i < WINDOWW; i++)
		for (int j = data->center; j < WINDOWW; j++)
			if(j  < WINDOWW && j > 0 && i < WINDOWW && i > 0)
				mlx_put_pixel(data->img, i, j, data->floorcolor);
	for (int i = 0; i < WINDOWW; i++)
		for (int j = 0; j < data->center; j++)
			if(j  < WINDOWW && j > 0 && i < WINDOWW && i > 0)
				mlx_put_pixel(data->img, i, j, data->ceilingcolor);
	if (data->player.angle >= 360)
		data->player.angle -= 360;
	else if (data->player.angle < 0)
		data->player.angle += 360;
	angle = data->player.angle - POV / 2;
	draw = 0;
	k = WINDOWW - 1;
	while (k >= 0)
	{
		a = angle;
		distance = hits(a,data) * cosf((a - data->player.angle) * M_PI / 180.0);
		wallheight = WINDOWW / distance;
		color = 0x964B00FF;
		if (data->ray.hitside == VERTICALE && data->ray.angle >= 0 && data->ray.angle <= 180)
			data->ray.texture = EAST;
		else if (data->ray.hitside == VERTICALE && data->ray.angle >= 180 && data->ray.angle <= 360)
			data->ray.texture = OUEST;
		else if (data->ray.hitside == HORIZONTALE && data->ray.angle >= 90 && data->ray.angle <= 270)
			data->ray.texture = NORD;
		else
			data->ray.texture = SUD;
		render_texture(data, k, wallheight);
		angle += POV / WINDOWW;
		draw += POV / WINDOWW;
		k--;
	}
	
	draw_cursor(data);
	draw_gun_normal(data);
	draw_map(data, data->map.height, data->map.width, WINDOWW / 100, 0x00FF0F);
	
	
}



int	my_mlx_loop_hook(t_data *data)
{
	\
	if (data->img != NULL)
		mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WINDOWW, WINDOWW);
	if (data->gamemode == STARTSCREEN)
		startscreen(data);
	if (data->gamemode == GAME)
		game(data);
	if (data->gamemode == STARTMENU)
		startmenu(data);
	if (data->gamemode == OPTIONS)
		options(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	return (0);
}



int	main(int c, char **v)
{
	t_data	data;
	t_data *data_ptr;
	data_ptr = &data;
	if(parser(c, v, data_ptr))
		return (0);
	// exit(0);
	data_ptr->player.speed = 0.01;
	data_ptr->player.rotation = 0.01;
	data_ptr->player.wpress = 0;
	data_ptr->player.spress = 0;
	data_ptr->player.dpress = 0;
	data_ptr->player.apress = 0;
	data_ptr->player.gun.state = 0;
	data_ptr->player.speed = 0.025;
	data_ptr->mouse.x = 0;
	data_ptr->mouse.y = 0;
	data_ptr->mouse.oldx = 0;
	data_ptr->mouse.oldy = 0;
	data_ptr->mouse.click = 0;
	data_ptr->mouse.anglemove = 0;
	data_ptr->mouse.centermove = 0;
	data_ptr->mouse.sensitivity = 0.1;
	data_ptr->center = 666;

	data_ptr->gamemode = STARTSCREEN;
	data_ptr->mlx = mlx_init(WINDOWW, WINDOWW, "CUB3D!", 1);
	load_cursor(data_ptr);
	load_walls_textures(data_ptr);
	load_normal_texture(data_ptr);
	load_loading_texture(data_ptr);
	data_ptr->map.map[4][5] = '1';
	data_ptr->map.map[5][4] = '1';
	data_ptr->img = NULL;
	mlx_loop_hook(data_ptr->mlx, (void *)my_mlx_loop_hook, data_ptr);
	mlx_key_hook(data_ptr->mlx, (void *)key_hook, data_ptr);
	mlx_mouse_hook(data_ptr->mlx, (void *)key_mouse, data_ptr);
	mlx_set_cursor_mode(data_ptr->mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(data_ptr->mlx, (void *)key_cursor, data_ptr);
	mlx_loop(data_ptr->mlx);
	mlx_terminate(data_ptr->mlx);
	return (0);
}
