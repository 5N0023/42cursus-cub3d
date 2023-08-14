/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:58:23 by mlektaib          #+#    #+#             */
/*   Updated: 2023/08/13 14:58:24 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void draw_map(t_data *data, int size, int color)
{
    int playerX = (int)data->player.x;
    int playerY = (int)data->player.y;
    int halfRange = 5; 

    for (int i = playerY - halfRange; i <= playerY + halfRange; i++)
    {
        for (int j = playerX - halfRange; j <= playerX + halfRange; j++)
        {
            if (i >= 0 && j >= 0 && j < data->map.width && i < data->map.height)
            {
				if(data->map.map[i][j] == '0')
					color = 0x2E3357FF;
                else
					color = 0x1A0E13FF;
                for (int k = 0; k < size; k++)
                {
                    for (int l = 0; l < size; l++)
                    {
                        int drawX = (j - (playerX - halfRange)) * size + l;
                        int drawY = (i - (playerY - halfRange)) * size + k;
                        mlx_put_pixel(data->img, drawX, drawY, color);
                    }
                }
			}
			else {
				color = 0x1A0E13FF;
				for (int k = 0; k < size; k++)
                {
                    for (int l = 0; l < size; l++)
                    {
                        int drawX = (j - (playerX - halfRange)) * size + l;
                        int drawY = (i - (playerY - halfRange)) * size + k;
                        mlx_put_pixel(data->img, drawX, drawY, color);
                    }
                }

            }
        }
    }
	int x = halfRange * size + ((size - 8)/2);
	int y = halfRange * size  + ((size - 8)/2);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			mlx_put_pixel(data->img, x + j, y + i, 0xFF0000FF);
}