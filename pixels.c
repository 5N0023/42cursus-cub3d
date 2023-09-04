#include "cub3D.h"

unsigned int	get_pixel(mlx_image_t *img, int i, int j)
{
	int	pos;

	pos = (j * 4 * img->width) + i * 4;
	return (ft_pixel(img->pixels[pos], img->pixels[pos + 1], img->pixels[pos
			+ 2], img->pixels[pos + 3]));
}

void	put_to_dataimg(t_data *data, mlx_image_t *image, int x, int y)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < image->width)
	{
		j = 0;
		while (j < image->height)
		{
			unsigned pixel = get_pixel(image, i, j);
			mlx_put_pixel(data->img, i + x, j + y, pixel);
			j++;
		}
		i++;
	}
}