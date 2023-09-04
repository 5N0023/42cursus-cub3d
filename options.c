#include "cub3D.h"

void	click_handler(t_data *data)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (x > 841 && y > 130 && x < 891 && y < 180 && data->mouse.click == 1
		&& data->mouse.sensitivity < 1)
		data->mouse.sensitivity += 0.01;
	if (x > 605 && y > 130 && x < 640 && y < 180 && data->mouse.click == 1
		&& data->mouse.sensitivity > 0.01)
		data->mouse.sensitivity -= 0.01;
	if (x > 841 && y > 330 && x < 891 && y < 380 && data->player.speed < 0.1
		&& data->mouse.click == 1)
		data->player.speed += 0.001;
	if (x > 605 && y > 330 && x < 650 && y < 380 && data->player.speed > 0
		&& data->mouse.click == 1)
		data->player.speed -= 0.001;
	if (x > 573 && y > 919 && x < 938 && y < 956 && data->mouse.click == 1)
		data->state = STARTMENU;
	if (x > 682 && y > 795 && x < 828 && y < 831 && data->mouse.click == 1)
	{
		data->player.speed = 0.05;
		data->mouse.sensitivity = 0.5;
	}
}

void	put_options_img(t_data *data, mlx_image_t *image)
{
	size_t	i;
	size_t	j;
	int	pixel;

	i = 0;
	while (i < image->width)
	{
		j = 0;
		while (j < image->height)
		{
			pixel = get_pixel(image, i, j);
			mlx_put_pixel(data->img, i, j, pixel);
			j++;
		}
		i++;
	}
	mlx_delete_image(data->mlx, image);
}

void	options(t_data *data)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	click_handler(data);
	texture = mlx_load_png("textures/options.png");
	if (!texture)
		exit(1);
	image = mlx_texture_to_image(data->mlx, texture);
	mlx_delete_texture(texture);
	mlx_resize_image(image, 1000, 1000);
	put_mouse_sensitive(data, image);
	put_player_speed(data, image);
	put_options_img(data, image);
}
