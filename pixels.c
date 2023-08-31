#include "cub3D.h"

unsigned int get_pixel(mlx_image_t *img,int i,int j)
{
	int pixel;
	uint8_t r;
	uint8_t b;
	uint8_t g;
	uint8_t a;
	int pos = (j * 4 * img->width) + i * 4;
	r = img->pixels[pos];
	g = img->pixels[pos+1];
	b = img->pixels[pos+2];
	a = img->pixels[pos+3];
	return(ft_pixel(r,g,b,a));
}

void put_to_dataimg(t_data *data,mlx_image_t *image,int x,int y)
{
	int  i;
	int j;

	i = 0;
	while(i < image->width)
	{
		j = 0;
		while(j < image->height)
		{
			unsigned pixel = get_pixel(image, i, j);
			mlx_put_pixel(data->img, i+x, j+y, pixel);
			j++;
		}
		i++;
	}
}