#include "cub3D.h"

void load_valorant_texture(t_data *data)
{
	mlx_texture_t *texture;
    data->player.gun.valorant.ult = malloc(sizeof(mlx_image_t*) * 139);
    data->player.gun.valorant.ultiframe = 0;
    data->player.gun.valorant.knifes = 5;
    char path2[50] = "textures/jett/frame-001.png";
    for(int i = 0;i < 139;i++)
    {
        path2[20] = (i+1) / 100 + '0';
        path2[21] = ((i+1) / 10) % 10 + '0';
        path2[22] = (i+1) % 10 + '0';
        texture = mlx_load_png(path2);
        data->player.gun.valorant.ult[i] = mlx_texture_to_image(data->mlx, texture);
        mlx_resize_image(data->player.gun.valorant.ult[i], 1000, 500);
        mlx_delete_texture(texture);
    }
}