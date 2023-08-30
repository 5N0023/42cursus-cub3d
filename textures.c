#include "cub3D.h"


extern double tester;


void draw_door(mlx_image_t *img,int pixelsline,double wallheight,t_data *data,int x)
{
    double k = img->height/2;
    int y = data->center;
    while( y < data->center + wallheight / 2 && y < WINDOWW)
    {
        int color;
        
        color = get_pixel(img,pixelsline,(int)k);
        k += 250 / wallheight;
        if(k >= 250)
            k = 249;
        if (y >= 0 && y < WINDOWW)
            mlx_put_pixel(data->img, x, y, color);
        y++;
    }
    y = data->center;
    k = img->height/2;
    while( y > data->center - wallheight / 2 && y >= 0)
    {
        int color;
        
        color = get_pixel(img,pixelsline,(int)k);
        k -= 250 / wallheight;
        if(k < 0)
            k = 0;
        if (y >= 0 && y < WINDOWW)
            mlx_put_pixel(data->img, x, y, color);
        y--;
    }
}


void load_walls_textures(t_data *data)
{
    mlx_texture_t *texture;
    mlx_image_t *img;
    texture = mlx_load_png(data->texture.nord);
    if(!texture)
            exit(1);
    img = mlx_texture_to_image(data->mlx, texture);
    mlx_resize_image(img, 250, 250);
    data->texture.nordimg = img;
    mlx_delete_texture(texture);
    texture = mlx_load_png(data->texture.sud);
    if(!texture)
            exit(1);
    img = mlx_texture_to_image(data->mlx, texture);
    mlx_resize_image(img, 250, 250);
    data->texture.sudimg = img;
    mlx_delete_texture(texture);
    texture = mlx_load_png(data->texture.east);
    if(!texture)
            exit(1);
    img = mlx_texture_to_image(data->mlx, texture);
    mlx_resize_image(img, 250, 250);
    data->texture.eastimg = img;
    mlx_delete_texture(texture);
    texture = mlx_load_png(data->texture.ouest);
    if(!texture)
            exit(1);
    img = mlx_texture_to_image(data->mlx, texture);
    mlx_resize_image(img, 250, 250);
    data->texture.ouestimg = img;
    mlx_delete_texture(texture);
}

void render_nord(t_data *data,int x,double wallheight)
{
    int pixelsline;
    pixelsline = (int)((data->ray.x - (int)data->ray.x) * 250);
    draw_door(data->texture.nordimg,pixelsline,wallheight,data,x);
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


void render_door_NS(t_data *data,int x,double wallheight,t_doorlist *tmp)
{
    int pixelsline;
    pixelsline = (int)((tmp->doorhitx - (int)tmp->doorhitx) * 250);
    double k = data->texture.door[0]->height /2;
    double y = data->center;
    while(y < data->center + wallheight / 2 && y < WINDOWW)
    {
        int color;
        color = get_pixel(data->texture.door[get_door_frame(tmp,data)],pixelsline,(int)k);
        k += 250 / wallheight;
        if(k >= 250)
            k = 249;
        if (y >= 0 && y < WINDOWW && color)
            mlx_put_pixel(data->img, x, y, color);
        y++;
    }

    k = data->texture.door[0]->height /2;
    y = data->center;
    while(y > data->center - wallheight / 2 && y >= 0)
    {
        int color;
        color = get_pixel(data->texture.door[get_door_frame(tmp,data)],pixelsline,(int)k);
        k -= 250 / wallheight;
        if(k < 0)
            k = 0;
        if (y >= 0 && y < WINDOWW && color)
            mlx_put_pixel(data->img, x, y, color);
        y--;
    }

}

void render_door_WE(t_data *data,int x,double wallheight,t_doorlist *tmp)
{
    int pixelsline;
    pixelsline = (int)((tmp->doorhity - (int)tmp->doorhity) * 250);
    double k = data->texture.door[0]->height /2;
    double y = data->center;
    while(y < data->center + wallheight / 2 && y < WINDOWW)
    {
        int color;
        color = get_pixel(data->texture.door[get_door_frame(tmp,data)],pixelsline,(int)k);
        k += 250 / wallheight;
        if(k >= 250)
            k = 249;
        if (y >= 0 && y < WINDOWW && color)
            mlx_put_pixel(data->img, x, y, color);
        y++;
    }

    k = data->texture.door[0]->height /2;
    y = data->center;
    while(y > data->center - wallheight / 2 && y >= 0)
    {
        int color;
        color = get_pixel(data->texture.door[get_door_frame(tmp,data)],pixelsline,(int)k);
        k -= 250 / wallheight;
        if(k < 0)
            k = 0;
        if (y >= 0 && y < WINDOWW && color)
            mlx_put_pixel(data->img, x, y, color);
        y--;
    }
}

void render_sud(t_data *data,int x,double wallheight)
{
    int pixelsline;
    pixelsline = (int)((data->ray.x - (int)data->ray.x) * 250);
    draw_door(data->texture.sudimg,pixelsline,wallheight,data,x);
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
    draw_door(data->texture.eastimg,pixelsline,wallheight,data,x);
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
    draw_door(data->texture.eastimg,pixelsline,wallheight,data,x);
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
    else if(data->ray.texture == OUEST)
        render_ouest(data,x,wallheight);
    else if(data->ray.texture == SUD)
        render_sud(data,x,wallheight);
    else if(data->ray.texture == EAST)
        render_east(data,x,wallheight);
    if (data->ray.doorlist)
    {
        t_doorlist *tmp;
        tmp = data->ray.doorlist;
        while(tmp)
        {
            tmp->doordistance *= cos((data->ray.angle - data->player.angle) * M_PI / 180);
            wallheight = WINDOWW / tmp->doordistance;
            if(tmp->doorhitside == NS && tmp->doordistance < data->ray.distance*cos((data->ray.angle - data->player.angle) * M_PI / 180))
                render_door_NS(data,x,wallheight,tmp);
            if(tmp->doorhitside == WE &&tmp->doordistance < data->ray.distance*cos((data->ray.angle - data->player.angle) * M_PI / 180))
                render_door_WE(data,x,wallheight,tmp);
            tmp = tmp->next;
        }
    }
    free_door_list(data);
}