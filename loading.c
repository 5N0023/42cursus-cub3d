#include "cub3D.h"

void load_loading_texture(t_data *data)
{
	mlx_texture_t *texture;
    data->loading.frames = malloc(sizeof(mlx_image_t*) * 105);
    char path2[50] = "textures/loading/frame_000.png";
    for(int i = 0;i < 106;i++)
    {
        texture = mlx_load_png(path2);
        data->loading.frames[i] = mlx_texture_to_image(data->mlx, texture);
        mlx_resize_image(data->loading.frames[i], 1000, 1000);
        mlx_delete_texture(texture);
        path2[23] = (i+1) / 100 + '0';
        path2[24] = ((1+i) / 10) % 10 + '0';
        path2[25] = (1 +i) % 10 + '0';
    }
}

void startscreen(t_data *data)
{
    static int f;
    for (int i = 0;i < data->loading.frames[f]->width;i++)
    {
        for (int j = 0;j < data->loading.frames[f]->height;j++)
        {
            unsigned pixel = get_pixel(data->loading.frames[f], i, j);
            mlx_put_pixel(data->img, i, j, pixel);
        }
    }
    mlx_delete_image(data->mlx, data->loading.frames[f]);
    f++;
    if (f == 106)
    {
        // mlx_set_mouse_pos(data->mlx, WINDOWW / 2, WINDOWW / 2);
	    mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
        f = 0;
        data->gamemode = STARTMENU;
    }
}