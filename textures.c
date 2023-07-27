#include "cub3D.h"

void load_walls_textures(t_data *data)
{
    mlx_texture_t *texture;
    mlx_image_t *img;
    texture = mlx_load_png("textures/wall.png");
    img = mlx_texture_to_image(data->mlx, texture);
    mlx_resize_image(img, 1000, 1000);
    mlx_delete_texture(texture);
    data->texture.nordimg = img;
    data->texture.sudimg = img;
    data->texture.eastimg = img;
    data->texture.ouestimg = img;

}

void render_nord(t_data *data,int x,double wallheight)
{
    int pixelsline;
    pixelsline = (int)((data->ray.x - (int)data->ray.x) * 1000);
    double k = 0;
    for(int y = data->center - wallheight / 2; y < data->center + wallheight / 2; y++)
    {
        int color;
        
        color = get_pixel(data->texture.nordimg,pixelsline,(int)k);
        k += 1000 / wallheight;
        if(k >= 1000)
            k = 999;
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
void render_sud(t_data *data,int x,double wallheight)
{
    int pixelsline;
    pixelsline = (int)((data->ray.x - (int)data->ray.x) * 1000);
    double k = 0;
    for(int y = data->center - wallheight / 2; y < data->center + wallheight / 2; y++)
    {
        int color;
        color = get_pixel(data->texture.sudimg,pixelsline,(int)k);
        k += 1000 / wallheight;
        if(k >= 1000)
            k = 999;
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
    pixelsline = ((int)((data->ray.y - (int)data->ray.y) * 1000));
    double k = 0;
    for(int y = data->center - wallheight / 2; y < data->center + wallheight / 2; y++)
    {
        int color;
        color = get_pixel(data->texture.ouestimg,pixelsline,(int)k);
        k += 1000 / wallheight;
        if(k >= 1000)
            k = 999;
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
    pixelsline = ((int)((data->ray.y - (int)data->ray.y) * 1000));
    double k = 0;
    for(int y = data->center - wallheight / 2; y < data->center + wallheight / 2; y++)
    {
        int color;
        color = get_pixel(data->texture.ouestimg,pixelsline,(int)k);
        k += 1000 / wallheight;
        if(k >= 1000)
            k = 999;
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
}