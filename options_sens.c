#include "cub3D.h"

void	put_number_pos(mlx_image_t *image, mlx_image_t *img, int x, int y)
{
	size_t	i;
	size_t	j;
	int	pixel;

	i = 0;
	while (i < img->width)
	{
		j = 0;
		while (j < img->height)
		{
			pixel = get_pixel(img, i, j);
			if (pixel << 24 != 0)
				mlx_put_pixel(image, i + x, j + y, pixel);
			j++;
		}
		i++;
	}
}

static void	put_numbers(mlx_image_t *image, mlx_image_t *numbers_img[3])
{
	put_number_pos(image, numbers_img[0], 675, 120);
	put_number_pos(image, numbers_img[1], 725, 120);
	put_number_pos(image, numbers_img[2], 775, 120);
}

void	calcul_sens_num(t_data *data, int numbers[3])
{
	int	mouse_sensitive;

	mouse_sensitive = (int)(data->mouse.sensitivity * 100);
	numbers[0] = mouse_sensitive / 100;
	numbers[1] = (mouse_sensitive / 10) % 10;
	numbers[2] = mouse_sensitive % 10;
}

mlx_image_t	*get_number_image(char *path, int number, t_data *data)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	path[17] = number + '0';
	texture = mlx_load_png(path);
	if (!texture)
		exit(1);
	image = mlx_texture_to_image(data->mlx, texture);
	mlx_delete_texture(texture);
	mlx_resize_image(image, 50, 50);
	return (image);
}

void	load_numbers_sen(t_data *data, mlx_image_t *numbers_img[3],
		int numbers[3])
{
	char	*path;

	path = ft_strdup("textures/numbers/0.png");
	numbers_img[0] = get_number_image(path, numbers[0], data);
	numbers_img[1] = get_number_image(path, numbers[1], data);
	numbers_img[2] = get_number_image(path, numbers[2], data);
	free(path);
}

void	put_mouse_sensitive(t_data *data, mlx_image_t *image)
{
	mlx_image_t *numbers_img[3];
	int numbers[3];

	calcul_sens_num(data, numbers);

	load_numbers_sen(data, numbers_img, numbers);
	put_numbers(image, numbers_img);
	mlx_delete_image(data->mlx, numbers_img[0]);
	mlx_delete_image(data->mlx, numbers_img[1]);
	mlx_delete_image(data->mlx, numbers_img[2]);
}