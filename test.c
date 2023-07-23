
#include "cub3D.h"



int hit = 0;

void draw_map(int x, int y, int size, int color, t_data *data)
{
    for(int i = 0; i < x; i++)
        for(int j = 0; j < y; j++)
            if(data->map->map[i][j] == '1')
                for(int k = 0; k < size; k++)
                    for(int l = 0; l < size; l++)
                        mlx_put_pixel(data->img, i * size + k, j * size + l, color);
            else if (data->map->map[i][j] == '0')
                for(int k = 0; k < size; k++)
                    for(int l = 0; l < size; l++)
                        mlx_put_pixel(data->img, i * size + k, j * size + l, 0x87CEEB0F);
    x = data->player->x * WINDOWW / 50 - 3;
    y = data->player->y * WINDOWW / 50 - 3;
    for(int i = 0; i < 6; i++)
        for(int j = 0; j < 6; j++)
            mlx_put_pixel(data->img, x + i, y + j, 0xFF5F1FF);
    
}


void draw_line(int x0, int y0, int x1, int y1,int color,t_data *data) {
    
    if (y0 < 0)
        y0 = 0;
    if (y0 >= WINDOWW)
        y0 = WINDOWW-1;
    if(y1 < 0)
        y1 = 0;
    if(x0 < 0)
        x0 = 0;
    if(y1 >= WINDOWW)
        y1 = WINDOWW-1;
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int  k = 0;
    while (1) {
        if (x0 < 0 || x0 > WINDOWW || y0 < 0 || y0 > WINDOWW)
            break;
        
        if (k == 0 && x0 != 0 && y0 != WINDOWW -1)
            mlx_put_pixel(data->img, x0, y0, 0x000000FF);
        else
            mlx_put_pixel(data->img, x0, y0, color);
        if (x0 == x1 && y0 == y1)
        {
            if (x0 != 0 && y0 != WINDOWW -1)
                mlx_put_pixel(data->img, x0, y0, 0x000000FF);
            break;
        }
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
        k++;
    }
}



void  castrayvertical(t_ray *vray, t_data *data) {
    double radian;

    if (vray->angle <= 90 && vray->angle >= 0)
        vray->dx = (int)vray->x + 1;
    else if (vray->angle >= 0 && vray->angle <= 180)
        vray->dx = (int)vray->x + 1;
    else if (vray->angle >= 180 && vray->angle <= 360)
        {
            if (vray->dx == (int)vray->x)
                vray->dx = (int)vray->x - 1;
            else
                vray->dx = (int)vray->x;
        }
    radian = vray->angle * M_PI / 180.0;
    if (vray->angle != 0 && vray->angle != 180 && vray->angle != 360)
        vray->dy = vray->y + (vray->dx - vray->x) / tanf(radian);
    else if (vray->angle == 0 || vray->angle == 180 || vray->angle == 360)
        {
            vray->dx = vray->x;
            if (vray->angle == 0 || vray->angle == 360)
                vray->dy = (int)vray->y + 1;
            else
                {
                    if (vray->dy != (int)vray->y)
                        vray->dy = (int)vray->y;
                    else
                        vray->dy = (int)vray->y - 1;
                }
        }
    vray->x = vray->dx;
    vray->y = vray->dy;
    if(vray->x  <= 0 || vray->x >= 10 || vray->y <= 0 || vray->y >= 10)
    {
        hit = 1;
        vray->x = vray->dx;
        vray->y = vray->dy;
        return;
    }
    if((vray->angle >= 180 && vray->angle <= 360) || vray->angle == 0)
        {
            if (data->map->map[(int)vray->dx - 1][(int)vray->dy] == '1')
                hit = 1;
        }
    if (data->map->map[(int)vray->dx][(int)vray->dy] == '1')
        hit = 1;
    
}

void castrayhorizontal(t_ray *hray, t_data *data) {
    double radian;

    radian = hray->angle * M_PI / 180.0;

    if (hray->angle >= 0 && hray->angle < 90)
        hray->dy = (int)hray->y+1;
    else if (hray->angle > 90 && hray->angle < 270)
        {
            if (hray->dy == (int)hray->y)
                hray->dy = (int)hray->y - 1;
            else
                hray->dy = (int)hray->y;
        }
    else
        hray->dy = (int)hray->y+1;

    if (hray->angle != 90 && hray->angle != 270) {
        hray->dx = hray->x + (hray->dy - hray->y) * tanf(radian);
    }
    else {
        hray->dy = hray->y;
        if (hray->angle == 90)
            hray->dx = (int)hray->x + 1;
        else
            if (hray->dx != (int)(hray->x))
                hray->dx = (int)hray->x;
            else
            {
                if(hray->dx == (int)hray->x)
                    hray->dx = (int)hray->x - 1;
                else
                    hray->dx = (int)hray->x;
            }
               
    }
    hray->x = hray->dx;
    hray->y = hray->dy;
    if(hray->x  < 0 || hray->x  > 10 || hray->y < 0 || hray->y > 10)
    {
        hit = 1;
        hray->x = hray->dx;
        hray->y = hray->dy;
        return;
    }
    if(hray->angle >= 90 && hray->angle <= 270)
        {
            if (data->map->map[(int)hray->dx][(int)hray->dy - 1] == '1')
                hit = 1;
        }
    if (data->map->map[(int)hray->dx][(int)hray->dy] == '1')
        hit = 1;
}

double hits(double angle,t_data *data)
{
    if (angle >= 360)
        angle -= 360;
    else if (angle < 0)
        angle += 360;
    t_ray hray;
    t_ray vray;
    data->ray->angle = angle;
    hray.angle = angle;
    hray.x = data->player->x;
    hray.y = data->player->y;
    hit = 0;
    while(!hit)
        castrayvertical(&vray,data);
    hit = 0;
    vray.angle = angle;
    vray.x = data->player->x;
    vray.y = data->player->y;
    while(!hit)
        castrayhorizontal(&hray, data);
    vray.distance = sqrtf(powf((vray.dx - data->player->x), 2) + powf((vray.dy - data->player->y), 2));
    hray.distance = sqrtf(powf((hray.dx - data->player->x), 2) + powf((hray.dy - data->player->y), 2));
    if (vray.distance < hray.distance)
    {
        data->ray->x = vray.dx;
        data->ray->y = vray.dy;
        data->ray->distance = vray.distance;

    }
    else
    {
        data->ray->x = hray.dx;
        data->ray->y = hray.dy;
        data->ray->distance = hray.distance;
    }
    return (data->ray->distance);
}







mlx_keyfunc key_hook(mlx_key_data_t key, t_data *data)
{
    double x = data->player->x;
    double y = data->player->y;
    double distance1;
    double distance2;
    if (key.key == MLX_KEY_ESCAPE)
        exit(0);
    if(key.key == MLX_KEY_RIGHT)
        data->player->angle -= data->player->rotation;
    if(key.key == MLX_KEY_LEFT)
        data->player->angle += data->player->rotation;
    if(key.key == MLX_KEY_S)
    {
        distance1 = hits(data->player->angle+10+180,data);
        distance2 = hits(data->player->angle-10+180,data);
        if (distance1 > 0.2 && distance2 > 0.2)
        {
            x += cosf((data->player->angle+90) * M_PI / 180.0) * data->player->speed;
            y -= sinf((data->player->angle+90) * M_PI / 180.0) * data->player->speed;
        }
    }
    if(key.key == MLX_KEY_W)
    {
        distance1 = hits(data->player->angle+10,data);
        distance2 = hits(data->player->angle-10,data);
        if (distance1 > 0.2 && distance2 > 0.2)
        {
            x -= cosf((data->player->angle+90) * M_PI / 180.0) * data->player->speed;
            y += sinf((data->player->angle+90) * M_PI / 180.0) * data->player->speed;
        }
    }
    if(key.key == MLX_KEY_D)
    {
        distance1 = hits(data->player->angle+10-90,data);
        distance2 = hits(data->player->angle-10-90,data);
        if (distance1 > 0.2 && distance2 > 0.2)
        {
        x -= cosf((data->player->angle) * M_PI / 180.0) * data->player->speed;
        y += sinf((data->player->angle) * M_PI / 180.0) * data->player->speed;
        }
    }
    if(key.key == MLX_KEY_A)
    {
        distance1 = hits(data->player->angle+10+90,data);
        distance2 = hits(data->player->angle-10+90,data);
        if (distance1 > 0.2 && distance2 > 0.2)
        {
        x += cosf((data->player->angle) * M_PI / 180.0) * data->player->speed;
        y -= sinf((data->player->angle) * M_PI / 180.0) * data->player->speed;
        }
    }
    data->player->x = x;
    data->player->y = y;
    return (NULL);
}

mlx_mousefunc key_mouse(mouse_key_t button,action_t action, modifier_key_t mods,t_data *data)
{
    
    return (NULL);
    
}
mlx_cursorfunc key_cursor(double x,double y,t_data *data)
{
    static double oldx;
    static double oldy;
    if (oldx < x)
        data->player->angle -= 5;
    else
        data->player->angle += 5;
    if (oldy < y)
        {if (data->center - 5 > 0)
            data->center -= 5;}
    else
        {if (data->center + 5 < WINDOWW)
            data->center += 5;}
    oldx = x;
    oldy = y;
    return (NULL);
}


int my_mlx_loop_hook(t_data *data)
{

    if(data->img != NULL)
        mlx_delete_image(data->mlx,data->img);
    data->img = mlx_new_image(data->mlx, WINDOWW, WINDOWW);
    for(int i = 0; i < WINDOWW; i++)
        for(int j = data->center; j < WINDOWW; j++)
            mlx_put_pixel(data->img, i, j, 0x362624FF);
    for(int i = 0; i < WINDOWW; i++)
        for(int j = 0; j < data->center; j++)
            mlx_put_pixel(data->img, i, j, 0x87CEEBFF);
    if(data->player->angle >= 360)
        data->player->angle -= 360;
    else if(data->player->angle < 0)
        data->player->angle += 360;
    double angle = data->player->angle - FOV / 2;
    if (angle < 0)
        angle += 360;
    if (angle >= 360)
        angle -= 360;
    double draw = 0;
    
    int k = WINDOWW - 1;
    while (k >= 0 )
    {
        
        double a = angle;
        double distance = hits(a,data) * cosf((a - data->player->angle) * M_PI / 180.0);
        
        if (distance == 0)
            distance = 0.001;
        double wallheight = (WINDOWW / distance) - 1;
        int color = 0x964B00FF;
        color = color - (int)(distance * 10);
        draw_line(k, data->center - wallheight / 2, k, data->center + wallheight / 2, color,data );
        angle += data->fov / WINDOWW;
        draw += data->fov  / WINDOWW;
        k--;
    }
    draw_map(10, 10, WINDOWW / 50, 0x00FF0F,data);
    mlx_image_to_window(data->mlx,data->img, 0, 0);
    return (0);
}


int main()
{
    t_data data;
    t_map map;
    t_player player;
    t_data *data_ptr = &data;
    t_ray ray;
    data_ptr->ray = &ray;
    data_ptr->map = &map;
    data_ptr->player = &player;

    data_ptr->map->width = 10;
    data_ptr->map->height = 10;
    data_ptr->map->map = (char **)malloc(10 * sizeof(char *));
    for (int i = 0; i < 10; i++) {
        data_ptr->map->map[i] = (char *)malloc(10 * sizeof(char));
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            data_ptr->map->map[i][j] = '0';
            if (i == 0 || i == 9 || j == 0 || j == 9) {
                data_ptr->map->map[i][j] = '1';
            }
        }
    }
    data_ptr->map->map[4][5] = '1';
    data_ptr->map->map[5][4] = '1';
    data_ptr->map->map[7][3] = '1';
    data_ptr->mlx = NULL;
    data_ptr->img = NULL;
    data_ptr->player->angle = 0;
    data_ptr->player->x = 2;
    data_ptr->player->y = 2;
    data_ptr->player->speed = 0.1;
    data_ptr->player->rotation = 2.5;
    data_ptr->center = WINDOWW / 2;
    data_ptr->fov = FOV;
    data_ptr->mlx = mlx_init(WINDOWW, WINDOWW, "CUB3D!",1);
    mlx_loop_hook(data_ptr->mlx, (void *)my_mlx_loop_hook, data_ptr);
    mlx_key_hook(data_ptr->mlx, (void *)key_hook, data_ptr);
    mlx_mouse_hook(data_ptr->mlx, (void *)key_mouse, data_ptr);
    mlx_set_cursor_mode(data_ptr->mlx, MLX_MOUSE_DISABLED);
    mlx_cursor_hook(data_ptr->mlx, (void *)key_cursor, data_ptr);
    mlx_loop(data_ptr->mlx);
    return (0);
}

