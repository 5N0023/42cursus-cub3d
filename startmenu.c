#include "cub3D.h"

void	hover_start(t_data *data)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png("textures/startmenu/hover_start.png");
	if (!texture)
		exit(1);
	image = mlx_texture_to_image(data->mlx, texture);
	mlx_delete_texture(texture);
	mlx_resize_image(image, 1000, 1000);
	put_to_dataimg(data, image, 0, 0);
	mlx_delete_image(data->mlx, image);
	if (data->mouse.click == 1)
	{
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
		mlx_set_mouse_pos(data->mlx, data->mouse.x, data->mouse.y);
		data->state = GAME;
		data->mouse.click = 0;
	}
}

void	hover_options(t_data *data)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png("textures/startmenu/hover_options.png");
	if (!texture)
		exit(1);
	image = mlx_texture_to_image(data->mlx, texture);
	mlx_delete_texture(texture);
	mlx_resize_image(image, 1000, 1000);
	put_to_dataimg(data, image, 0, 0);
	mlx_delete_image(data->mlx, image);
	if (data->mouse.click == 1)
		data->state = OPTIONS;
}

void	hover_exit(t_data *data)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png("textures/startmenu/hover_exit.png");
	if (!texture)
		exit(1);
	image = mlx_texture_to_image(data->mlx, texture);
	mlx_delete_texture(texture);
	mlx_resize_image(image, 1000, 1000);
	put_to_dataimg(data, image, 0, 0);
	mlx_delete_image(data->mlx, image);
	if (data->mouse.click == 1)
		mlx_close_window(data->mlx);
}

void	nothing_hovered(t_data *data)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png("textures/startmenu/start_menu.png");
	if (!texture)
		exit(1);
	image = mlx_texture_to_image(data->mlx, texture);
	mlx_delete_texture(texture);
	mlx_resize_image(image, 1000, 1000);
	put_to_dataimg(data, image, 0, 0);
	mlx_delete_image(data->mlx, image);
}

void	startmenu(t_data *data)
{
	int x;
	int y;

	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (x > 40 && x < 326 && y > 237 && y < 308)
		hover_start(data);
	else if (x > 40 && x < 421 && y > 472 && y < 552)
		hover_options(data);
	else if (x > 40 && x < 214 && y > 707 && y < 777)
		hover_exit(data);
	else
		nothing_hovered(data);
}