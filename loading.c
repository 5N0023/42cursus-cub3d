/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:58:36 by mlektaib          #+#    #+#             */
/*   Updated: 2023/08/20 21:05:26 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void load_loading_texture(t_data *data)
{
	mlx_texture_t *texture;
    int i;
    char path2[50] = "textures/loading/frame_000.png";

    i = 0;
    data->loading.frames = malloc(sizeof(mlx_image_t*) * 105);
    while(i < 106)
    {
        texture = mlx_load_png(path2);
        if(!texture)
            exit(1);
        data->loading.frames[i] = mlx_texture_to_image(data->mlx, texture);
        mlx_resize_image(data->loading.frames[i], 1000, 1000);
        mlx_delete_texture(texture);
        path2[23] = (i+1) / 100 + '0';
        path2[24] = ((1+i) / 10) % 10 + '0';
        path2[25] = (1 +i) % 10 + '0';
        i++;
    }
}

void startscreen(t_data *data)
{
    static int f;
    int i;
    int j;

    i = 0;
    while (i < data->loading.frames[f]->width)
    {
        j = 0;
        while (j < data->loading.frames[f]->height)
        {
            unsigned pixel = get_pixel(data->loading.frames[f], i, j);
            mlx_put_pixel(data->img, i, j, pixel);
            j++;
        }
        i++;
    }
    mlx_delete_image(data->mlx, data->loading.frames[f]);
    f++;
    if (f == 106)
    {
        mlx_set_mouse_pos(data->mlx, WINDOWW / 2, WINDOWW / 2);
	    mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
        f = 0;
        data->state = STARTMENU;
    }
}