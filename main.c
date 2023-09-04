/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:58:31 by mlektaib          #+#    #+#             */
/*   Updated: 2023/09/03 20:59:38 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double			tester;

mlx_mousefunc	key_mouse(mouse_key_t button, action_t action,
		modifier_key_t modifier_key, t_data *data)
{
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		data->mouse.click = 1;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		data->mouse.click = 0;
	return (NULL);
}
mlx_cursorfunc	key_cursor(double x, double y, t_data *data)
{
	if (data->state == GAME)
	{
		data->mouse.x = x;
		data->mouse.y = y;
	}
	return (NULL);
}

int	game_loop(t_data *data)
{
	tester = 0;
	if (data->img != NULL)
		mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WINDOWW, WINDOWW);
	if (data->state == STARTSCREEN)
		startscreen(data);
	if (data->state == GAME)
		game(data);
	if (data->state == STARTMENU)
		startmenu(data);
	if (data->state == OPTIONS)
		options(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	return (0);
}

void	checkleaks(void)
{
	system("leaks cub3D");
}

void	clear_leaks(t_data *data)
{
	int	i;

	free(data->texture.door);
	free(data->player.gun.normal.bullets);
	free(data->player.gun.normal.gunshoot);
	free(data->player.gun.normal.gunreload);
	free(data->loading.frames);
	free(data->texture.nord);
	free(data->texture.sud);
	free(data->texture.east);
	free(data->texture.ouest);
	i = 0;
	while (i < data->map.height)
	{
		free(data->map.map[i]);
		i++;
	}
	free(data->map.map);
}

int	main(int c, char **v)
{
	t_data	data;
	t_data	*data_ptr;

	data_ptr = &data;
	atexit(checkleaks);
	if (parser(c, v, data_ptr))
		return (1);
	data_ptr->mlx = initdefaultval(data_ptr);
	load_cursor(data_ptr);
	load_walls_textures(data_ptr);
	load_normal_texture(data_ptr);
	door_textures(data_ptr);
	load_loading_texture(data_ptr);
	data_ptr->img = NULL;
	mlx_loop_hook(data_ptr->mlx, (void *)game_loop, data_ptr);
	mlx_key_hook(data_ptr->mlx, (void *)key_hook, data_ptr);
	mlx_mouse_hook(data_ptr->mlx, (void *)key_mouse, data_ptr);
	mlx_set_cursor_mode(data_ptr->mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(data_ptr->mlx, (void *)key_cursor, data_ptr);
	mlx_loop(data_ptr->mlx);
	mlx_terminate(data.mlx);
	clear_leaks(data_ptr);
	return (0);
}
