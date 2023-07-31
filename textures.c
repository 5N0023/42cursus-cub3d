#include "cub3D.h"

void load_walls_textures(t_data *data)
{
    mlx_texture_t *texture;
    mlx_image_t *img;
    texture = mlx_load_png("textures/wall.png");
    img = mlx_texture_to_image(data->mlx, texture);
    mlx_resize_image(img, 250, 250);
    mlx_delete_texture(texture);
    data->texture.nordimg = img;
    data->texture.sudimg = img;
    data->texture.eastimg = img;
    data->texture.ouestimg = img;
}

void render_nord(t_data *data,int x,double wallheight)
{
    int pixelsline;
    pixelsline = (int)((data->ray.x - (int)data->ray.x) * 250);
    double k = 0;
    for(int y = data->center - wallheight / 2; y < data->center + wallheight / 2; y++)
    {
        int color;
        
        color = get_pixel(data->texture.nordimg,pixelsline,(int)k);
        k += 250 / wallheight;
        if(k >= 250)
            k = 249;
        if (y >= 0 && y < WINDOWW)
            mlx_put_pixel(data->img, x, y, color);
    }
     int i = 0;
    if(data->center - wallheight / 2 > 0)
    {
        i = data->center - wallheight / 2;
        for (int y = 0; y < i; y++)
            if (y >= 0 && y < WINDOWW)
                mlx_put_pixel(data->img, x, y, data->ceilingcolor);
    }
    if (data->center + wallheight / 2 < WINDOWW)
    {
        i = data->center + wallheight / 2;
        for (int y = i; y < WINDOWW; y++)
        if (y >= 0 && y < WINDOWW)
            mlx_put_pixel(data->img, x, y, data->floorcolor);
    }

}


void render_door_NE(t_data *data,int x,double wallheight)
{
    int pixelsline;
    pixelsline = (int)((data->ray.doorhitx - (int)data->ray.doorhitx) * 250);
    double k = 0;
    for(int y = data->center - wallheight / 2; y < data->center + wallheight / 2; y++)
    {
        int color;
        if(data->ray.doordistance < 0.2 && door_state(data,data->ray.doorhitx,data->ray.doorhity) == OPENED)
            break;
        color = get_pixel(data->texture.door[get_door_frame(data)],pixelsline,(int)k);
        k += 250 / wallheight;
        if(k >= 250)
            k = 249;
        if (y >= 0 && y < WINDOWW && color)
            mlx_put_pixel(data->img, x, y, color);
    }

}

void render_door_WE(t_data *data,int x,double wallheight)
{
    int pixelsline;
    pixelsline = (int)((data->ray.doorhity - (int)data->ray.doorhity) * 250);
    double k = 0;
    double y = data->center - wallheight / 2;
    while(y < data->center + wallheight / 2)
    {
        int color;
        if(data->ray.doordistance < 0.3 && door_state(data,data->ray.doorhitx,data->ray.doorhity) == OPENED)
            break;
        color = get_pixel(data->texture.door[get_door_frame(data)],pixelsline,(int)k);
        k += 250 / wallheight;
        if(k >= 250)
            k = 249;
        if (y >= 0 && y < WINDOWW && color)
            mlx_put_pixel(data->img, x, y, color);
        y++;
    }

}

void render_sud(t_data *data,int x,double wallheight)
{
    int pixelsline;
    pixelsline = (int)((data->ray.x - (int)data->ray.x) * 250);
    double k = 0;
    for(int y = data->center - wallheight / 2; y < data->center + wallheight / 2; y++)
    {
        int color;
        color = get_pixel(data->texture.sudimg,pixelsline,(int)k);
        k += 250 / wallheight;
        if(k >= 250)
            k = 249;
        if (y >= 0 && y < WINDOWW)
            mlx_put_pixel(data->img, x, y, color);
    }
     int i = 0;
    if(data->center - wallheight / 2 > 0)
    {
        i = data->center - wallheight / 2;
        for (int y = 0; y < i; y++)
            if (y >= 0 && y < WINDOWW)
                mlx_put_pixel(data->img, x, y, data->ceilingcolor);
    }
    if (data->center + wallheight / 2 < WINDOWW)
    {
        i = data->center + wallheight / 2;
        for (int y = i; y < WINDOWW; y++)
        if (y >= 0 && y < WINDOWW)
            mlx_put_pixel(data->img, x, y, data->floorcolor);
    }
}

void render_east(t_data *data,int x,double wallheight)
{
    int pixelsline;
    pixelsline = ((int)((data->ray.y - (int)data->ray.y) * 250));
    double k = 0;
    for(int y = data->center - wallheight / 2; y < data->center + wallheight / 2; y++)
    {
        int color;
        color = get_pixel(data->texture.ouestimg,pixelsline,(int)k);
        k += 250 / wallheight;
        if(k >= 250)
            k = 249;
        if (y >= 0 && y < WINDOWW)
            mlx_put_pixel(data->img, x, y, color);
    }
    int i = 0;
   if(data->center - wallheight / 2 > 0)
    {
        i = data->center - wallheight / 2;
        for (int y = 0; y < i; y++)
            if (y >= 0 && y < WINDOWW)
                mlx_put_pixel(data->img, x, y, data->ceilingcolor);
    }
    if (data->center + wallheight / 2 < WINDOWW)
    {
        i = data->center + wallheight / 2;
        for (int y = i; y < WINDOWW; y++)
            if (y >= 0 && y < WINDOWW)
                mlx_put_pixel(data->img, x, y, data->floorcolor);
    }
}

void render_ouest(t_data *data,int x,double wallheight)
{
    int pixelsline;
    pixelsline = ((int)((data->ray.y - (int)data->ray.y) * 250));
    double k = 0;
    for(int y = data->center - wallheight / 2; y < data->center + wallheight / 2; y++)
    {
        int color;
        color = get_pixel(data->texture.ouestimg,pixelsline,(int)k);
        k += 250 / wallheight;
        if(k >= 250)
            k = 249;
        if (y >= 0 && y < WINDOWW)
            mlx_put_pixel(data->img, x, y, color);
    }
    int i = 0;
    if(data->center - wallheight / 2 > 0)
    {
        i = data->center - wallheight / 2;
        for (int y = 0; y < i; y++)
            if (y >= 0 && y < WINDOWW)
                mlx_put_pixel(data->img, x, y, data->ceilingcolor);
    }
    if (data->center + wallheight / 2 < WINDOWW)
    {
        i = data->center + wallheight / 2;
        for (int y = i; y < WINDOWW; y++)
        if (y >= 0 && y < WINDOWW)
            mlx_put_pixel(data->img, x, y, data->floorcolor);
    }
}


void render_texture(t_data *data,int x,double wallheight)
{
    if(data->ray.texture == NORD)
        render_nord(data,x,wallheight);
    else if(data->ray.texture == SUD)
            render_sud(data,x,wallheight);
    else if(data->ray.texture == EAST)
        render_east(data,x,wallheight);
    else if(data->ray.texture == OUEST)
        render_ouest(data,x,wallheight);
    if(data->ray.doorhit  && data->ray.doorhitside == NS && data->ray.distance > data->ray.doordistance)
    {
        data->ray.doordistance = data->ray.doordistance * cosf((data->ray.angle - data->player.angle) * M_PI / 180.0); 
        wallheight = WINDOWW / data->ray.doordistance;
        render_door_NE(data,x,wallheight);
    }
    else if(data->ray.doorhit  && data->ray.doorhitside == WE&& data->ray.distance > data->ray.doordistance)
    {
        data->ray.doordistance = data->ray.doordistance * cosf((data->ray.angle - data->player.angle) * M_PI / 180.0); 
        wallheight = WINDOWW / data->ray.doordistance;
        render_door_WE(data,x,wallheight);
    }
}