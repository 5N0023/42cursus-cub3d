#include "cub3D.h"

void startmenu(t_data *data)
{
    mlx_texture_t *texture;
    mlx_image_t *image;
    
    int x;
    int y;
    if (data->mouse.x > 40 && data->mouse.x < 326 && data->mouse.y > 237 && data->mouse.y < 308)
    {
        texture = mlx_load_png("textures/startmenu/hover_start.png");
        image = mlx_texture_to_image(data->mlx, texture);
        mlx_resize_image(image, 1000, 1000);
        for(int i = 0;i < 1000;i++)
        {
            for(int j = 0;j < 1000;j++){
                unsigned pixel = get_pixel(image, i, j);
                mlx_put_pixel(data->img, i, j, pixel);}
        }
        mlx_delete_image(data->mlx, image);
        if(data->mouse.click == 1)
        {
            mlx_set_mouse_pos(data->mlx, data->player.angle, data->center);
            mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
            data->gamemode = GAME;
            data->mouse.click = 0;
        }
    }
    else if (data->mouse.x > 40 && data->mouse.x < 421 && data->mouse.y > 472 && data->mouse.y < 552)
    {
        texture = mlx_load_png("textures/startmenu/hover_options.png");
        image = mlx_texture_to_image(data->mlx, texture);
        mlx_resize_image(image, 1000, 1000);
        for(int i = 0;i < 1000;i++)
        {
            for(int j = 0;j < 1000;j++){
                unsigned pixel = get_pixel(image, i, j);
                mlx_put_pixel(data->img, i, j, pixel);}
        }
        mlx_delete_image(data->mlx, image);
        if (data->mouse.click == 1)
            data->gamemode = OPTIONS;
    }
    else if (data->mouse.x > 40 && data->mouse.x < 214 && data->mouse.y > 707 && data->mouse.y < 777)
    {
        texture = mlx_load_png("textures/startmenu/hover_exit.png");
        image = mlx_texture_to_image(data->mlx, texture);
        mlx_resize_image(image, 1000, 1000);
        for(int i = 0;i < 1000;i++)
        {
            for(int j = 0;j < 1000;j++){
                unsigned pixel = get_pixel(image, i, j);
                mlx_put_pixel(data->img, i, j, pixel);}
        }
        mlx_delete_image(data->mlx, image);
        if(data->mouse.click == 1)
            exit(0);
    }
    else
    {
    texture = mlx_load_png("textures/startmenu/start_menu.png");
    image = mlx_texture_to_image(data->mlx, texture);
    mlx_resize_image(image, 1000, 1000);
    for(int i = 0;i < image->width;i++)
    {
        for(int j = 0;j < image->height;j++){
            unsigned pixel = get_pixel(image, i, j);
            mlx_put_pixel(data->img, i, j, pixel);}
    }
    mlx_delete_image(data->mlx, image);
    }
}