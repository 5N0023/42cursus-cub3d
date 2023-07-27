


#include "cub3D.h"

void put_mouse_sensitive(t_data *data,mlx_image_t *image)
{
    mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
    mlx_image_t *img;

    int mouse_sensitive = (int)(data->mouse.sensitivity * 100);
    char path[50] = "textures/numbers/0.png";
    int first = mouse_sensitive / 100;
    int second = (mouse_sensitive / 10) % 10;
    int third = mouse_sensitive % 10;
    mlx_image_t *first_img;
    mlx_image_t *second_img;
    mlx_image_t *third_img;
    mlx_texture_t *texture;

    path[17] = first + '0';
    texture = mlx_load_png(path);
    first_img = mlx_texture_to_image(data->mlx, texture);
    mlx_delete_texture(texture);
    mlx_resize_image(first_img, 50, 50);
    path[17] = second + '0';
    texture = mlx_load_png(path);
    second_img = mlx_texture_to_image(data->mlx, texture);
    mlx_delete_texture(texture);
    mlx_resize_image(second_img, 50, 50);
    path[17] = third + '0';
    texture = mlx_load_png(path);
    third_img = mlx_texture_to_image(data->mlx, texture);
    mlx_delete_texture(texture);
    mlx_resize_image(third_img, 50, 50);
    for(int i = 0;i < first_img->width;i++)
    {
        for(int j = 0;j < first_img->height;j++){
            unsigned pixel = get_pixel(first_img, i, j);
            if(pixel)
            mlx_put_pixel(image, i+675, j+120, pixel);}
    }

    for(int i = 0;i < second_img->width;i++)
    {
        for(int j = 0;j < second_img->height;j++){
            unsigned pixel = get_pixel(second_img, i, j);
            if(pixel)
            mlx_put_pixel(image, i+725, j+120, pixel);}
    }
    for(int i = 0;i < third_img->width;i++)
    {
        for(int j = 0;j < third_img->height;j++){
            unsigned pixel = get_pixel(third_img, i, j);
            if(pixel)
            mlx_put_pixel(image, i+775, j+120, pixel);}
    }
    mlx_delete_image(data->mlx, first_img);
    mlx_delete_image(data->mlx, second_img);
    mlx_delete_image(data->mlx, third_img);
}

void put_player_speed(t_data *data,mlx_image_t *image)
{
    mlx_image_t *img;

    int player_speed = (int)(data->player.speed * 1000);
    char path[50] = "textures/numbers/0.png";
    int first = player_speed / 100;
    int second = (player_speed / 10) % 10;
    int third = player_speed % 10;
    mlx_image_t *first_img;
    mlx_image_t *second_img;
    mlx_image_t *third_img;
    mlx_texture_t *texture;

    path[17] = first + '0';
    texture = mlx_load_png(path);
    first_img = mlx_texture_to_image(data->mlx, texture);
    mlx_delete_texture(texture);
    mlx_resize_image(first_img, 50, 50);
    path[17] = second + '0';
    texture = mlx_load_png(path);
    second_img = mlx_texture_to_image(data->mlx, texture);
    mlx_delete_texture(texture);
    mlx_resize_image(second_img, 50, 50);
    path[17] = third + '0';
    texture = mlx_load_png(path);
    third_img = mlx_texture_to_image(data->mlx, texture);
    mlx_delete_texture(texture);
    mlx_resize_image(third_img, 50, 50);
    for(int i = 0;i < first_img->width;i++)
    {
        for(int j = 0;j < first_img->height;j++){
            unsigned pixel = get_pixel(first_img, i, j);
            if(pixel)
            mlx_put_pixel(image, i+675, j+320, pixel);}
    }

    for(int i = 0;i < second_img->width;i++)
    {
        for(int j = 0;j < second_img->height;j++){
            unsigned pixel = get_pixel(second_img, i, j);
            if(pixel)
            mlx_put_pixel(image, i+725, j+320, pixel);}
    }
    for(int i = 0;i < third_img->width;i++)
    {
        for(int j = 0;j < third_img->height;j++){
            unsigned pixel = get_pixel(third_img, i, j);
            if(pixel)
            mlx_put_pixel(image, i+775, j+320, pixel);}
    }
    mlx_delete_image(data->mlx, first_img);
    mlx_delete_image(data->mlx, second_img);
    mlx_delete_image(data->mlx, third_img);
}

void options(t_data *data)
{
    mlx_texture_t *texture;
    mlx_image_t *image;

    int x;
    int y;
    mlx_get_mouse_pos(data->mlx, &x, &y);
    if (x > 841 && y > 130 && x < 891 && y < 180)
    {
        if (data->mouse.click == 1 && data->mouse.sensitivity < 1)
            data->mouse.sensitivity += 0.01;
    }
    if (x > 605 && y > 130 && x < 640 && y < 180)
    {
        if (data->mouse.click == 1 && data->mouse.sensitivity > 0.01)
            data->mouse.sensitivity -= 0.01;
    }
    if (x > 841 && y > 330 && x < 891 && y < 380)
    {
        if (data->player.speed < 0.1 && data->mouse.click == 1)
            data->player.speed += 0.001;
    }
    if (x > 605 && y > 330 && x < 650 && y < 380)
    {
        if (data->player.speed > 0.001 && data->mouse.click == 1)
            data->player.speed -= 0.001;
    }
    if (x > 573 && y > 919 && x < 938 && y < 956)
    {
        if (data->mouse.click == 1)
            data->gamemode = STARTMENU;
    }
    texture = mlx_load_png("textures/options.png");
    
    image = mlx_texture_to_image(data->mlx, texture);
    mlx_resize_image(image, 1000, 1000);
    put_mouse_sensitive(data, image);
    put_player_speed(data,image);
    for(int i = 0;i < image->width;i++)
    {
        for(int j = 0;j < image->height;j++){
            unsigned pixel = get_pixel(image, i, j);
            mlx_put_pixel(data->img, i, j, pixel);}
    }
    mlx_delete_image(data->mlx, image);
}