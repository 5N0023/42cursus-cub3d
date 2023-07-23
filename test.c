#include "cub3D.h"


double			hitx = 0;
double			hity = 0;
double			xray = -1;
double			yray = -1;
int				hit = 0;
double			hhitx = 0;
double			hhity = 0;
double			vhitx = 0;
double			vhity = 0;

void	draw_map(t_data *data, int x, int y, int size, int color)
{
	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
			if (data->map.map[i][j] == '1')
				for (int k = 0; k < size; k++)
					for (int l = 0; l < size; l++)
						mlx_put_pixel(data->img, i * size + k, j * size + l, color);
			else if (data->map.map[i][j] == '0')
				for (int k = 0; k < size; k++)
					for (int l = 0; l < size; l++)
						mlx_put_pixel(data->img, i * size + k, j * size + l,
							0x87CEEB0F);
	x = data->player.x * WINDOWW / 50 - 3;
	y = data->player.y * WINDOWW / 50 - 3;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			mlx_put_pixel(data->img, x + i, y + j, 0xFF5F1FF);
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
		if (x0 < 0 || x0 > WINDOWW || y0 < 0 || y0 > WINDOWW)
			break ;
		if (k == 0 && x0 != 0 && y0 != WINDOWW - 1)
			mlx_put_pixel(data->img, x0, y0, 0x000000FF);
		else
			mlx_put_pixel(data->img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
		{
			if (x0 != 0 && y0 != WINDOWW - 1)
				mlx_put_pixel(data->img, x0, y0, 0x000000FF);
			break ;
		}
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

void	castrayvertical(t_hit *vhit, double angle, char **map)
{
	double	pa;

	vhit->dx = 150;
	vhit->dy = 150;
	double radian;
	pa = angle;
	if (pa > 360)
		pa -= 360;
	if (pa < 0)
		pa += 360;
	if (pa <= 90 && pa >= 0)
		vhit->dx = (int)vhit->x + 1;
	else if (pa >= 0 && pa <= 180)
		vhit->dx = (int)vhit->x + 1;
	else if (pa >= 180 && pa <= 360)
	{
		if (vhit->dx == (int)vhit->x)
			vhit->dx = (int)vhit->x - 1;
		else
			vhit->dx = (int)vhit->x;
	}
	radian = pa * M_PI / 180.0;
	if (pa != 0 && pa != 180 && pa != 360)
		vhit->dy = vhit->y + (vhit->dx - vhit->x) / tanf(radian);
	else if (pa == 0 || pa == 180 || pa == 360)
	{
		vhit->dx = vhit->x;
		if (pa == 0 || pa == 360)
			vhit->dy = (int)vhit->y + 1;
		else
		{
			if (vhit->dy != (int)vhit->y)
				vhit->dy = (int)vhit->y;
			else
				vhit->dy = (int)vhit->y - 1;
		}
	}
	vhit->x = vhit->dx;
	vhit->y = vhit->dy;
	vhit->distance = sqrtf(powf((vhit->x - xray), 2) + powf((vhit->y - yray), 2));
	if (vhit->x < 0 || vhit->x > 10 || vhit->y < 0 || vhit->y > 10)
	{
		vhit->hit = 1;
		return ;
	}
	if (map[(int)vhit->dx][(int)vhit->dy] == '1')
		vhit->hit = 1;
	if (pa >= 180 || pa <= 90)
	{
		if (map[(int)vhit->dx - 1][(int)vhit->dy] == '1')
			vhit->hit = 1;
	}
}

void	castrayhorizontal(double x, double y, double angle, char **map)
{
	double	pa;

	double dx, dy, radian;
	pa = angle;
	if (pa >= 360)
		pa -= 360;
	else if (pa < 0)
		pa += 360;
	radian = pa * M_PI / 180.0;
	if (pa >=270 || pa < 90)
		dy = (int)y + 1;
	else if (pa > 90 && pa < 270)
	{
		if (dy == (int)y)
			dy = (int)y - 1;
		else
			dy = (int)y;
	}
	else
		dy = (int)y + 1;
	if (pa != 90 && pa != 270)
	{
		dx = x + (dy - y) * tanf(radian);
	}
	else
	{
		dy = y;
		if (pa == 90)
			dx = (int)x + 1;
		else if (dx != (int)(x))
			dx = (int)x;
		else
		{
			if (dx == (int)x)
				dx = (int)x - 1;
			else
				dx = (int)x;
		}
	}
	xray = dx;
	yray = dy;
		printf("vhit->x %f vhit->y %f angle %f \n", xray, yray, angle);
	if (xray < 0 || xray > 10 || yray < 0 || yray > 10)
	{
		hit = 1;
		xray = dx;
		yray = dy;
		return ;
	}
	if (pa >= 90 && pa <= 270)
	{
		if (map[(int)dx][(int)dy - 1] == '1')
			hit = 1;
	}
	if (map[(int)dx][(int)dy] == '1')
		hit = 1;
}

double	hits(double angle,t_data *data)
{
	double	vhitx;
	double	vhity;
	double	hhitx;
	double	hhity;
	double	vdistance;
	double	hdistance;
	double	distance;
	t_hit	vhit;

	vhit.hitx = WINDOWW;
	vhit.hity = WINDOWW;
	vhit.x = data->player.x;
	vhit.hit = 0;
	vhit.y = data->player.y;
	vhit.dx = WINDOWW;
	vhit.dy = WINDOWW;


	xray = data->player.x;
	yray = data->player.y;
	if (angle >= 360)
		angle -= 360;
	else if (angle < 0)
		angle += 360;
	vhitx = WINDOWW;
	vhity = WINDOWW;
	hhitx = WINDOWW;
	hhity = WINDOWW;
	xray = data->player.x;
	yray = data->player.y;
	hit = 0;
	while (!vhit.hit)
		castrayvertical(&vhit, angle, data->map.map);
	vhitx = vhit.x;
	vhity = vhit.y;
	xray = data->player.x;
	yray = data->player.y;
	hit = 0;
	while (!hit)
		castrayhorizontal(xray, yray, angle, data->map.map);
	hhitx = xray;
	hhity = yray;
	vdistance = sqrtf(powf((vhitx - data->player.x), 2) + powf((vhity - data->player.y), 2));
	hdistance = sqrtf(powf((hhitx - data->player.x), 2) + powf((hhity - data->player.y), 2));
	if (hdistance < vdistance)
	{
		hitx = hhitx;
		hity = hhity;
		distance = hdistance;
	}
	else
	{
		hitx = vhitx;
		hity = vhity;
		distance = vdistance;
	}
	return (distance);
}

void	move_player(t_data *data)
{
	double	x;
	double	y;
	double	distance1;
	double	distance2;
	x = data->player.x;
	y = data->player.y;
	if (data->player.spress)
	{
		distance1 = hits(data->player.angle + 10 + 180,data);
		distance2 = hits(data->player.angle - 10 + 180,data);
		if (distance1 > 0.2 && distance2 > 0.2)
		{
			x += cosf((data->player.angle + 90) * M_PI / 180.0) * 0.01;
			y -= sinf((data->player.angle + 90) * M_PI / 180.0) * 0.01;
		}
		printf("distance1 %f distance2 %f \n", distance1, distance2);
	}
	if (data->player.wpress)
	{
		distance1 = hits(data->player.angle + 10, data);
		distance2 = hits(data->player.angle - 10,data);
		if (distance1 > 0.2 && distance2 > 0.2)
		{
			x -= cosf((data->player.angle + 90) * M_PI / 180.0) * 0.01;
			y += sinf((data->player.angle + 90) * M_PI / 180.0) * 0.01;
		}
	}
	if (data->player.dpress)
	{
		distance1 = hits(data->player.angle + 10 - 90,data);
		distance2 = hits(data->player.angle - 10 - 90,data);
		if (distance1 > 0.2 && distance2 > 0.2)
		{
			x -= cosf((data->player.angle)*M_PI / 180.0) * 0.01;
			y += sinf((data->player.angle)*M_PI / 180.0) * 0.01;
		}
	}
	if (data->player.apress)
	{
		distance1 = hits(data->player.angle + 10 + 90,data);
		distance2 = hits(data->player.angle - 10 + 90,data);
		if (distance1 > 0.2 && distance2 > 0.2)
		{
			x += cosf((data->player.angle)*M_PI / 180.0) * 0.01;
			y -= sinf((data->player.angle)*M_PI / 180.0) * 0.01;
		}
	}
	data->player.angle+=data->mouse.anglemove*2;
    if(data->mouse.centermove > 0 && data->center < WINDOWW + 5 + 1)
        data->center+=data->mouse.centermove * 5;
    else if(data->mouse.centermove < 0 && data->center > 5)
        data->center+=data->mouse.centermove * 5;
	data->player.x = x;
	data->player.y = y;
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
	return (NULL);
}

mlx_mousefunc	key_mouse(mouse_key_t button, action_t action,
		modifier_key_t modifier_key, void *param)
{
	
	return (NULL);
}
mlx_cursorfunc	key_cursor(double x, double y, t_data *data)
{
	data->mouse.x = x;
	data->mouse.y = y;
	if (data->mouse.oldx < data->mouse.x -10)
		data->mouse.anglemove = -1;
	else if (data->mouse.oldx > data->mouse.x +10)
		data->mouse.anglemove = 1;
	else
		data->mouse.anglemove = 0;
	if (data->mouse.oldy < y - 10)
		data->mouse.centermove = -1;
	else if (data->mouse.oldy > y + 10)
		data->mouse.centermove = 1;
    else
		data->mouse.centermove = 0;
	data->mouse.oldx = x;
	data->mouse.oldy = y;
	return (NULL);
}

int	my_mlx_loop_hook(t_data *data)
{
	double	POV;
	double	angle;
	double	draw;
	int		k;
	double	a;
	double	distance;
	double	wallheight;
	int		color;

	
	if (data->img != NULL)
		mlx_delete_image(data->mlx, data->img);
	POV = 60;
	data->img = mlx_new_image(data->mlx, WINDOWW, WINDOWW);
	for (int i = 0; i < WINDOWW; i++)
		for (int j = data->center; j < WINDOWW; j++)
			mlx_put_pixel(data->img, i, j, 0x00FFFF);
	for (int i = 0; i < WINDOWW; i++)
		for (int j = 0; j < data->center; j++)
			mlx_put_pixel(data->img, i, j, 0x87CEEBFF);
	if (data->player.angle >= 360)
		data->player.angle -= 360;
	else if (data->player.angle < 0)
		data->player.angle += 360;
	angle = data->player.angle - POV / 2;
	if (angle < 0)
		angle += 360;
	if (angle >= 360)
		angle -= 360;
	draw = 0;
	k = WINDOWW - 1;
	while (k >= 0)
	{
		a = angle;
		distance = hits(a,data) * cosf((a - data->player.angle) * M_PI / 180.0);
		wallheight = WINDOWW / distance;
		color = 0x964B00FF;
		color = color - (int)(distance * 10);
		draw_line(k, data->center - wallheight / 2, k, data->center + wallheight / 2, color, data);
		angle += POV / WINDOWW;
		draw += POV / WINDOWW;
		k--;
	}
	draw_map(data, 10, 10, WINDOWW / 50, 0x00FF0F);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
    move_player(data);
	return (0);
}

int	main(void)
{
	t_data	data;
	t_data *data_ptr;
	data_ptr = &data;
	data_ptr->player.x = 1.1;
	data_ptr->player.y = 1.1;
	data_ptr->player.speed = 0.01;
	data_ptr->player.rotation = 0.01;
	data_ptr->player.angle = 0;
	data_ptr->player.wpress = 0;
	data_ptr->player.spress = 0;
	data_ptr->player.dpress = 0;
	data_ptr->player.apress = 0;
	data_ptr->mouse.x = 0;
	data_ptr->mouse.y = 0;
	data_ptr->mouse.oldx = 0;
	data_ptr->mouse.oldy = 0;
	data_ptr->mouse.click = 0;
	data_ptr->mouse.anglemove = 0;
	data_ptr->mouse.centermove = 0;
	data_ptr->center = WINDOWW / 2;

	data_ptr->map.map= (char **)malloc(10 * sizeof(char *));
	data_ptr->map.width = 10;
	data_ptr->map.height = 10;
	for (int i = 0; i < 10; i++)
	{
		data_ptr->map.map[i] = (char *)malloc(10 * sizeof(char));
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			data_ptr->map.map[i][j] = '0';
			if (i == 0 || i == 9 || j == 0 || j == 9)
				data_ptr->map.map[i][j] = '1';
		}
	}
	data_ptr->map.map[4][5] = '1';
	data_ptr->map.map[5][4] = '1';
	data_ptr->img = NULL;
	data_ptr->mlx = mlx_init(WINDOWW, WINDOWW, "CUB3D!", 1);
	mlx_loop_hook(data_ptr->mlx, (void *)my_mlx_loop_hook, data_ptr);
	mlx_key_hook(data_ptr->mlx, (void *)key_hook, data_ptr);
	mlx_mouse_hook(data_ptr->mlx, (void *)key_mouse, data_ptr);
	mlx_set_cursor_mode(data_ptr->mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(data_ptr->mlx, (void *)key_cursor, data_ptr);
	mlx_loop(data_ptr->mlx);
	return (0);
}
