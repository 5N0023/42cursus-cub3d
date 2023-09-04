/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_wall_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:42:34 by mlektaib          #+#    #+#             */
/*   Updated: 2023/09/04 22:42:41 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

mlx_image_t	*load_wall_texture_path(char *path, t_data *data)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(path);
	if (!texture)
		exit(1);
	img = mlx_texture_to_image(data->mlx, texture);
	mlx_resize_image(img, 250, 250);
	mlx_delete_texture(texture);
	return (img);
}

void	load_walls_textures(t_data *data)
{
	data->texture.nordimg = load_wall_texture_path(data->texture.nord, data);
	data->texture.sudimg = load_wall_texture_path(data->texture.sud, data);
	data->texture.eastimg = load_wall_texture_path(data->texture.east, data);
	data->texture.ouestimg = load_wall_texture_path(data->texture.ouest, data);
}
