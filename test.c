#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "MLX42/MLX42.h"
#include <math.h>
#define SPEED 0.2
#define WINDOWW 1000

void *mlx_ptr;
int posx = 50;
int posy = 50;
mlx_image_t *img = NULL;
mlx_image_t *img2 = NULL;


double playerx = 2;
double playery = 2;
double playerangel = 45 +180;
double hitx = 0;
double hity = 0;
int **map;
double xray = -1;
double yray = -1;
int hit = 0;
double hhitx = 0;
double hhity = 0;
double vhitx = 0;
double vhity = 0;
double equal = WINDOWW / 2;




void draw_map(int **map, int x, int y, int size, int color)
{
    for(int i = 0; i < x; i++)
        for(int j = 0; j < y; j++)
            if(map[i][j] == 1)
                for(int k = 0; k < size; k++)
                    for(int l = 0; l < size; l++)
                        mlx_put_pixel(img, i * size + k, j * size + l, color);
            else if (map[i][j] == 0)
                for(int k = 0; k < size; k++)
                    for(int l = 0; l < size; l++)
                        mlx_put_pixel(img, i * size + k, j * size + l, 0x87CEEB0F);
    x = playerx * WINDOWW / 50 - 3;
    y = playery * WINDOWW / 50 - 3;
    for(int i = 0; i < 6; i++)
        for(int j = 0; j < 6; j++)
            mlx_put_pixel(img, x + i, y + j, 0xFF5F1FF);
    
}


void draw_line(int x0, int y0, int x1, int y1,int color) {
    
    if (y0 < 0)
        y0 = 0;
    if (y0 > WINDOWW)
        y0 = WINDOWW;
    if(y1 < 0)
        y1 = 0;
    if(x0 < 0)
        x0 = 0;
    if(y1 > WINDOWW)
        y1 = WINDOWW;
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    while (1) {
        if (x0 < 0 || x0 > WINDOWW || y0 < 0 || y0 > WINDOWW)
            break;
        mlx_put_pixel(img, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}



void  castrayvertical(double x, double y, double angle, int **map) {
    double dx, dy, radian;
    double pa = angle;
    
    if(pa > 360)
        pa -= 360;
    if (pa < 0)
        pa += 360;
    if (pa <= 90 && pa >= 0)
        dx = (int)x + 1;
    else if (pa >= 0 && pa <= 180)
        dx = (int)x + 1;
    else if (pa >= 180 && pa <= 360)
        {
            if (dx == (int)x)
                dx = (int)x - 1;
            else
                dx = (int)x;
        }
    radian = pa * M_PI / 180.0;
    if (pa != 0 && pa != 180 && pa != 360)
        dy = y + (dx - x) / tanf(radian);
    else if (pa == 0 || pa == 180 || pa == 360)
        {
            dx = x;
            if (pa == 0 || pa == 360)
                dy = (int)y + 1;
            else
                {
                    if (dy != (int)y)
                        dy = (int)y;
                    else
                        dy = (int)y - 1;
                }
        }
    xray = dx;
    yray = dy;
    if(xray < 0 || xray > 10 || yray < 0 || yray > 10)
    {
        hit = 1;
        xray = dx;
        yray = dy;
        return;
    }
    if(pa >= 180 || pa <= 90)
        {
            if (map[(int)dx - 1][(int)dy] == 1)
                hit = 1;
        }
    if (map[(int)dx][(int)dy] == 1)
        hit = 1;
    
}

void castrayhorizontal(double x, double y, double angle, int **map) {
    double dx, dy, radian;
    double pa = angle;

    if (pa >= 360)
        pa -= 360;
    else if (pa < 0)
        pa += 360;

    radian = pa * M_PI / 180.0;

    if (pa >= 0 && pa < 90)
        dy = (int)y+1;
    else if (pa > 90 && pa < 270)
        {
            if (dy == (int)y)
                dy = (int)y - 1;
            else
                dy = (int)y;
        }
    else
        dy = (int)y+1;

    if (pa != 90 && pa != 270) {
        dx = x + (dy - y) * tanf(radian);
    }
    else {
        dy = y;
        if (pa == 90)
            dx = (int)x + 1;
        else
            if (dx != (int)(x))
                dx = (int)x;
            else
            {
                if(dx == (int)x)
                    dx = (int)x - 1;
                else
                    dx = (int)x;
            }
               
    }
    xray = dx;
    yray = dy;
    if(xray < 0 || xray > 10 || yray < 0 || yray > 10)
    {
        hit = 1;
        xray = dx;
        yray = dy;
        return;
    }
    if(pa >= 90 && pa <= 270)
        {
            if (map[(int)dx][(int)dy - 1] == 1)
                hit = 1;
        }
    if (map[(int)dx][(int)dy] == 1)
        hit = 1;
}

double hits(double angle)
{
    xray = playerx;
    yray = playery;
    if (angle >= 360)
        angle -= 360;
    else if (angle < 0)
        angle += 360;
    double vhitx = WINDOWW;
    double vhity = WINDOWW;
    double hhitx = WINDOWW;
    double hhity = WINDOWW;
    xray = playerx;
    yray = playery;
    hit = 0;
    while(!hit)
        castrayvertical(xray, yray, angle, map);
    vhitx = xray;
    vhity = yray;
    xray = playerx;
    yray = playery;
    hit = 0;
    while(!hit)
        castrayhorizontal(xray, yray, angle, map);
    hhitx = xray;
    hhity = yray;
    double vdistance = sqrtf(powf((vhitx - playerx), 2) + powf((vhity - playery), 2));
    double hdistance = sqrtf(powf((hhitx - playerx), 2) + powf((hhity - playery), 2));
    double distance;
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
    return(distance);
}







mlx_keyfunc key_hook(int key, void *param)
{
    double x = playerx;
    double y = playery;
    if (key == MLX_KEY_ESCAPE)
        exit(0);
    if(key == MLX_KEY_RIGHT)
        playerangel += 5;
    if(key == MLX_KEY_LEFT)
        playerangel -= 5;
    if(key == MLX_KEY_S)
    {
        x += cosf((playerangel+90) * M_PI / 180.0) * SPEED;
        y -= sinf((playerangel+90) * M_PI / 180.0) * SPEED;
    }
    if(key == MLX_KEY_W)
    {
        x -= cosf((playerangel+90) * M_PI / 180.0) * SPEED;
        y += sinf((playerangel+90) * M_PI / 180.0) * SPEED;
    }
    if(key == MLX_KEY_A)
    {
        x -= cosf((playerangel) * M_PI / 180.0) * SPEED;
        y += sinf((playerangel) * M_PI / 180.0) * SPEED;
    }
    if(key == MLX_KEY_D)
    {
        x += cosf((playerangel) * M_PI / 180.0) * SPEED;
        y -= sinf((playerangel) * M_PI / 180.0) * SPEED;
    }
   if(map[(int)x][(int)y] == 0)
    {
        playerx = x;
        playery = y;
    }
    return (NULL);
}

mlx_mousefunc key_mouse(mouse_key_t button,action_t action, modifier_key_t modifier_key,void *param)
{
    if(button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
        printf("left click at %d %d\n",posx,posy);
    if(button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
        printf("right click at %d %d\n",posx,posy);
    if(button == MLX_MOUSE_BUTTON_MIDDLE && action == MLX_PRESS)
        printf("middle click at %d %d\n",posx,posy);
    if(button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
        printf("left release at %d %d\n",posx,posy);
    if(button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_RELEASE)
        printf("right release at %d %d\n",posx,posy);
    if(button == MLX_MOUSE_BUTTON_MIDDLE && action == MLX_RELEASE)
        printf("middle release at %d %d\n",posx,posy);
    printf("button %d action %d modifier %d\n",button,action,modifier_key);
    return (NULL);
    
}
mlx_cursorfunc key_cursor(double x,double y,void *param)
{
    if (x < 0 || x > WINDOWW || y < 0 || y > WINDOWW)
        return (NULL);
    
    playerangel = (int)fabs(x) % 360;
    equal = (WINDOWW - ((int)fabs(y)% WINDOWW));
    printf("cursor at %f %f\n",x,y);
    return (NULL);
}


int my_mlx_loop_hook(void *param)
{

    if(img != NULL)
        mlx_delete_image(mlx_ptr,img);
    double POV = 60;
    img = mlx_new_image(mlx_ptr, WINDOWW, WINDOWW);
    draw_map(map, 10, 10, WINDOWW / 50, 0x00FFFF);
    for(int i = 0; i < WINDOWW; i++)
        for(int j = equal; j < WINDOWW; j++)
            mlx_put_pixel(img, i, j, 0x00FFFF);
    for(int i = 0; i < WINDOWW; i++)
        for(int j = 0; j < equal; j++)
            mlx_put_pixel(img, i, j, 0x87CEEBFF);
    if(playerangel >= 360)
        playerangel -= 360;
    else if(playerangel < 0)
        playerangel += 360;
    double angle = playerangel - POV / 2;
    if (angle < 0)
        angle += 360;
    if (angle >= 360)
        angle -= 360;
    double draw = 0;
    int k = 0;
    
    while (k < WINDOWW)
    {
        double a = angle;
        double distance = hits(a);
        double wallheight = WINDOWW / distance;
        int color = 0x964B00FF;
        color = color - (int)(distance * 10);
        draw_line(k, equal - wallheight / 2, k, equal + wallheight / 2, color );
        angle += POV / WINDOWW;
        draw += POV / WINDOWW;
        k++;
    }
    draw_map(map, 10, 10, WINDOWW / 50, 0x00FF0F);
    mlx_image_to_window(mlx_ptr, img, 0, 0);
    return (0);
}


int main()
{
    map = (int **)malloc(10 * sizeof(int *));
    for (int i = 0; i < 10; i++) {
        map[i] = (int *)malloc(10 * sizeof(int));
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            map[i][j] = 0;
            if (i == 0 || i == 9 || j == 0 || j == 9) {
                map[i][j] = 1;
            }
        }
    }
    map[4][5] = 1;
    map[5][4] = 1;
    img = NULL;
    mlx_ptr = mlx_init(WINDOWW, WINDOWW, "CUB3D!",1);
    mlx_loop_hook(mlx_ptr, (void *)my_mlx_loop_hook, NULL);
    mlx_key_hook(mlx_ptr, (void *)key_hook, NULL);
    mlx_mouse_hook(mlx_ptr, (void *)key_mouse, NULL);
    // mlx_set_cursor_mode(mlx_ptr, MLX_MOUSE_DISABLED);
    mlx_cursor_hook(mlx_ptr, (void *)key_cursor, NULL);
    mlx_loop(mlx_ptr);
    return (0);
}

