#include "cub3D.h"

void startmenu(t_data *data)
{
    mlx_texture_t *texture;
    mlx_image_t *image;
    
    int x;
    int y;
    mlx_get_mouse_pos(data->mlx, &x, &y);
    if (x > 40 && x < 326 && y > 237 && y < 308)
    {
        texture = mlx_load_png("textures/startmenu/hover_start.png");
        if(!texture)
            exit(1);
        image = mlx_texture_to_image(data->mlx, texture);
        mlx_delete_texture(texture);
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
            mlx_set_mouse_pos(data->mlx, data->mouse.x, data->mouse.y);
            mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
            data->state = GAME;
            data->mouse.click = 0;
        }
    }
    else if (x > 40 && x < 421 && y > 472 && y < 552)
    {
        texture = mlx_load_png("textures/startmenu/hover_options.png");
        if(!texture)
            exit(1);
        image = mlx_texture_to_image(data->mlx, texture);
        mlx_delete_texture(texture);
        mlx_resize_image(image, 1000, 1000);
        for(int i = 0;i < 1000;i++)
        {
            for(int j = 0;j < 1000;j++){
                unsigned pixel = get_pixel(image, i, j);
                mlx_put_pixel(data->img, i, j, pixel);}
        }
        mlx_delete_image(data->mlx, image);
        if (data->mouse.click == 1)
            data->state = OPTIONS;
    }
    else if (x > 40 && x < 214 && y > 707 && y < 777)
    {
        texture = mlx_load_png("textures/startmenu/hover_exit.png");
        if(!texture)
            exit(1);
        image = mlx_texture_to_image(data->mlx, texture);
        mlx_delete_texture(texture);
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
    if(!texture)
            exit(1);
    image = mlx_texture_to_image(data->mlx, texture);
    mlx_delete_texture(texture);
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