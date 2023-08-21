#include "cub3D.h"


extern double tester;
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


void render_door_NS(t_data *data,int x,double wallheight,t_doorlist *tmp)
{
    int pixelsline;
    pixelsline = (int)((tmp->doorhitx - (int)tmp->doorhitx) * 250);
    double k = 0;
    for(int y = data->center - wallheight / 2; y < data->center + wallheight / 2; y++)
    {
        int color;
        if(tmp->doordistance < 0.2 && door_state(data,tmp->doorhitx,tmp->doorhity) == OPENED)
            break;
        color = get_pixel(data->texture.door[get_door_frame(tmp,data)],pixelsline,(int)k);
        k += 250 / wallheight;
        if(k >= 250)
            k = 249;
        if (y >= 0 && y < WINDOWW && color)
            mlx_put_pixel(data->img, x, y, color);
    }

}

void render_door_WE(t_data *data,int x,double wallheight,t_doorlist *tmp)
{
    int pixelsline;
    pixelsline = (int)((tmp->doorhity - (int)tmp->doorhity) * 250);
    double k = 0;
    double y = data->center - wallheight / 2;
    while(y < data->center + wallheight / 2)
    {
        int color;
        if(tmp->doordistance < 0.3 && door_state(data,tmp->doorhitx,tmp->doorhity) == OPENED)
            break;
        color = get_pixel(data->texture.door[get_door_frame(tmp,data)],pixelsline,(int)k);
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
        color = get_pixel(data->texture.eastimg,pixelsline,(int)k);
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


void render_sprite(t_data *data,double x,double spritesize,t_spritelist *tmp)
{
    double k = 0;

    if(tester >= 250)
        return;
    for(int y = data->center - spritesize / 2; y < data->center + spritesize / 2; y++)
    {
        int color;
        color = get_pixel(data->texture.sprite[data->texture.spriteframe],(int)tester,(int)k);
        k += 250 / spritesize;
        if(k >= 250)
            k = 249;
        if (y >= 0 && y < WINDOWW && color)
            mlx_put_pixel(data->img, x, y, color);
    }
    tester += 250 / spritesize;
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
            tmp->doordistance *= cosf((data->ray.angle - data->player.angle) * M_PI / 180);
            wallheight = WINDOWW / tmp->doordistance;
            if(tmp->doorhitside == NS && tmp->doordistance < data->ray.distance*cosf((data->ray.angle - data->player.angle) * M_PI / 180))
                render_door_NS(data,x,wallheight,tmp);
            if(tmp->doorhitside == WE &&tmp->doordistance < data->ray.distance*cosf((data->ray.angle - data->player.angle) * M_PI / 180))
                render_door_WE(data,x,wallheight,tmp);
            tmp = tmp->next;
        }
    }
    if (data->ray.spritelist)
    {
        t_spritelist *tmp;
        tmp = data->ray.spritelist;
        // while(tmp)
        // {
            tmp->spritedistance *= cosf((data->ray.angle - data->player.angle) * M_PI / 180);
            wallheight = WINDOWW / tmp->spritedistance;
            if(tmp->spritedistance < data->ray.distance*cosf((data->ray.angle - data->player.angle) * M_PI / 180) && tmp->spritedistance/cosf((data->ray.angle - data->player.angle) * M_PI / 180)  > 1)
                render_sprite(data,x,wallheight/2,tmp);
        //     tmp = tmp->next;
        // }
    }
    free_door_list(data);
    free_sprites_list(data);
}