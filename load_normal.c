#include "cub3D.h"





void draw_gun_normal(t_data *data)
{
	static int f ;
    static int k;
    mlx_image_t *string;
	for(int i = 0;i < data->player.gun.normal.bullets[data->player.gun.normal.bullet]->height;i++)
			{
				for(int j = 0;j < data->player.gun.normal.bullets[data->player.gun.normal.bullet]->height;j++){
					unsigned pixel = get_pixel(data->player.gun.normal.bullets[data->player.gun.normal.bullet], i, j);
					if (pixel)
						mlx_put_pixel(data->img, i+50, j+(WINDOWW -data->player.gun.normal.bullets[data->player.gun.normal.bullet]->height), pixel);}
			}
	if (data->player.gun.state == RELOAD && data->player.gun.normal.bullet < 24)
	{
		for(int i = 0;i < data->player.gun.normal.gunreload[f/2]->width;i++)
			{
				for(int j = 0;j < data->player.gun.normal.gunreload[f/2]->height;j++){
					unsigned pixel = get_pixel(data->player.gun.normal.gunreload[f/2], i, j);
					if (pixel)
						mlx_put_pixel(data->img, i+200, j+(WINDOWW - data->player.gun.normal.gunreload[f/2]->height), pixel);}
			}
		f++;
		if (f == 45*2)
		{
            data->player.gun.normal.bullet = 24;
			f = 0;
			data->player.gun.state = 0;
		}
	}
    else if (data->player.gun.state == SHOOT && data->player.gun.normal.bullet > 0)
    {
        
        for(int i = 0;i < data->player.gun.normal.gunshoot[f/2]->width;i++)
			{
				for(int j = 0;j < data->player.gun.normal.gunshoot[f/2]->height;j++){
					unsigned pixel = get_pixel(data->player.gun.normal.gunshoot[f/2], i, j);
					if (pixel)
						mlx_put_pixel(data->img, i+200, j+(WINDOWW - data->player.gun.normal.gunshoot[f/2]->height), pixel);}
			}
		f++;
        if (!k)
        {
            data->player.gun.normal.bullet--;
            k = 1;
        }
		if (f == 8*2)
        {
			f = 0;
            k = 0;
            data->player.gun.state = 0;
        }
    }
    else 
	{
        f = 0;
        k = 0;
		for(int i = 0;i < data->player.gun.normal.gunshoot[5]->width;i++)
			{
				for(int j = 0;j < data->player.gun.normal.gunshoot[5]->height;j++){
					unsigned pixel = get_pixel(data->player.gun.normal.gunshoot[5], i, j);
					if (pixel)
						mlx_put_pixel(data->img, i+200, j+(WINDOWW - data->player.gun.normal.gunshoot[5]->height), pixel);}
			}
        data->player.gun.state = 0;
	}
}



void load_normal_texture(t_data *data)
{
	mlx_texture_t *texture;
    data->player.gun.normal.bullet = 24;
    data->player.gun.normal.gunreload = malloc(sizeof(mlx_image_t*) * 47);
    char path2[50] = "textures/normal/reload/frame_01_delay-0.02s.png";
    for(int i = 0;i < 46;i++)
    {
        texture = mlx_load_png(path2);
        data->player.gun.normal.gunreload[i] = mlx_texture_to_image(data->mlx, texture);
        mlx_resize_image(data->player.gun.normal.gunreload[i], 640, 400);
        mlx_delete_texture(texture);
        path2[29] = (i+1) / 10 + '0';
        path2[30] = (i+1) % 10 + '0';
    }
    data->player.gun.normal.gunshoot = malloc(sizeof(mlx_image_t*) * 10);
    char path[50] = "textures/normal/shoot/frame_00.png";
    for(int i = 0;i < 9;i++)
    {
        texture = mlx_load_png(path);
        data->player.gun.normal.gunshoot[i] = mlx_texture_to_image(data->mlx, texture);
        mlx_resize_image(data->player.gun.normal.gunshoot[i], 640, 400);
        mlx_delete_texture(texture);
        path[28] = (i+1) / 10 + '0';
        path[29] = (i+1) % 10 + '0';
    }
     data->player.gun.normal.bullets = malloc(sizeof(mlx_image_t*) * 25);
    char path3[50] = "textures/normal/bullets/00.png";
    for(int i = 0;i < 25;i++)
    {
        texture = mlx_load_png(path3);
        data->player.gun.normal.bullets[i] = mlx_texture_to_image(data->mlx, texture);
        mlx_resize_image(data->player.gun.normal.bullets[i], 100, 100);
        mlx_delete_texture(texture);
        path3[24] = (i+1) / 10 + '0';
        path3[25] = (i+1) % 10 + '0';
    }
}