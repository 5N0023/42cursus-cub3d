#include "cub3D.h"



void load_reload_animation(t_data *data)
{
    char path[50] = "textures/normal/reload/frame_01_delay-0.02s.png";
    int i;
    mlx_texture_t *texture;

    i = 0;
    data->player.gun.normal.gunreload = malloc(sizeof(mlx_image_t*) * 47);
    while(i < 46)
    {
        texture = mlx_load_png(path);
        if(!texture)
            exit(1);
        data->player.gun.normal.gunreload[i] = mlx_texture_to_image(data->mlx, texture);
        mlx_resize_image(data->player.gun.normal.gunreload[i], 640, 400);
        mlx_delete_texture(texture);
        path[29] = (i+1) / 10 + '0';
        path[30] = (i+1) % 10 + '0';
        i++;
    }
}

void load_shoot_animation(t_data *data)
{
    char path[50] = "textures/normal/shoot/frame_00.png";
    mlx_texture_t *texture;
    int i;

    i = 0;
    data->player.gun.normal.gunshoot = malloc(sizeof(mlx_image_t*) * 10);
    while(i < 9)
    {
        texture = mlx_load_png(path);
        if(!texture)
            exit(1);
        data->player.gun.normal.gunshoot[i] = mlx_texture_to_image(data->mlx, texture);
        mlx_resize_image(data->player.gun.normal.gunshoot[i], 640, 400);
        mlx_delete_texture(texture);
        path[28] = (i+1) / 10 + '0';
        path[29] = (i+1) % 10 + '0';
        i++;
    }
}

void load_bullets_count(t_data *data)
{
    mlx_texture_t *texture;
    int i;
    char path[50] = "textures/normal/bullets/00.png";

    i = 0;
    data->player.gun.normal.bullets = malloc(sizeof(mlx_image_t*) * 25);
    while(i < 25)
    {
        texture = mlx_load_png(path);
        if(!texture)
            exit(1);
        data->player.gun.normal.bullets[i] = mlx_texture_to_image(data->mlx, texture);
        mlx_resize_image(data->player.gun.normal.bullets[i], 100, 100);
        mlx_delete_texture(texture);
        path[24] = (i+1) / 10 + '0';
        path[25] = (i+1) % 10 + '0';
        i++;
    }
}

void load_normal_texture(t_data *data)
{
	mlx_texture_t *texture;

    data->player.gun.normal.bullet = 24;
    load_reload_animation(data);
    load_shoot_animation(data);
    load_bullets_count(data);
}