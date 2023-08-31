#include "cub3D.h"

void put_number_pos(mlx_image_t *image,mlx_image_t *img,int x,int y)
{
	int  i;
	int j;

	i = 0;
	while(i < img->width)
	{
		j = 0;
		while(j < img->height)
		{
			unsigned pixel = get_pixel(img, i, j);
			if(pixel >> 24 == 255)
			mlx_put_pixel(image, i+x, j+y, pixel);
			j++;
		}
		i++;
	}
}

static void put_numbers(mlx_image_t *image,mlx_image_t *numbers_img[3])
{
	
    put_number_pos(image,numbers_img[0],675,120);
    put_number_pos(image,numbers_img[1],725,120);
    put_number_pos(image,numbers_img[2],775,120);
  
}

void calcul_sens_num(t_data *data, int numbers[3])
{
    int mouse_sensitive;

    mouse_sensitive = (int)(data->mouse.sensitivity * 100);
    numbers[0] = mouse_sensitive / 100;
    numbers[1] = (mouse_sensitive / 10) % 10;
    numbers[2] = mouse_sensitive % 10;
}

void load_numbers_sen(t_data *data, mlx_image_t *numbers_img[3], int numbers[3])
{
    mlx_texture_t *texture;
    char path[50]= "textures/numbers/0.png";

    path[17] = numbers[0] + '0';
    texture = mlx_load_png(path);
    if(!texture)
            exit(1);
    numbers_img[0] = mlx_texture_to_image(data->mlx, texture);
    mlx_delete_texture(texture);
    mlx_resize_image(numbers_img[0], 50, 50);
    path[17] = numbers[1] + '0';
    texture = mlx_load_png(path);
    if(!texture)
            exit(1);
    numbers_img[1] = mlx_texture_to_image(data->mlx, texture);
    mlx_delete_texture(texture);
    mlx_resize_image(numbers_img[1], 50, 50);
    path[17] = numbers[2] + '0';
    texture = mlx_load_png(path);
    if(!texture)
            exit(1);
    numbers_img[2] = mlx_texture_to_image(data->mlx, texture);
    mlx_delete_texture(texture);
    mlx_resize_image(numbers_img[2], 50, 50);
}

void put_mouse_sensitive(t_data *data,mlx_image_t *image)
{
    mlx_image_t *img;

    int numbers[3];

    calcul_sens_num(data, numbers);
    mlx_image_t *numbers_img[3];

    load_numbers_sen(data, numbers_img, numbers);
    put_numbers(image, numbers_img);
    mlx_delete_image(data->mlx, numbers_img[0]);
    mlx_delete_image(data->mlx, numbers_img[1]);
    mlx_delete_image(data->mlx, numbers_img[2]);
}