#include "cub3D.h"

static void put_numbers(mlx_image_t *image,mlx_image_t *numbers_img[3])
{
	
    put_number_pos(image,numbers_img[0],675,320);
    put_number_pos(image,numbers_img[1],725,320);
    put_number_pos(image,numbers_img[2],775,320);
  
}

void calcul_ps_num(t_data *data, int numbers[3])
{
    int playerspeed;

    playerspeed = (int)(data->player.speed * 1000);
    numbers[0] = playerspeed / 100;
    numbers[1] = (playerspeed / 10) % 10;
    numbers[2] = playerspeed % 10;
}

void load_numbers_ps(t_data *data, mlx_image_t *numbers_img[3], int numbers[3])
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

void put_player_speed(t_data *data,mlx_image_t *image)
{
    mlx_image_t *img;

    int numbers[3];

    calcul_ps_num(data, numbers);
    mlx_image_t *numbers_img[3];

    load_numbers_ps(data, numbers_img, numbers);
    put_numbers(image, numbers_img);
    mlx_delete_image(data->mlx, numbers_img[0]);
    mlx_delete_image(data->mlx, numbers_img[1]);
    mlx_delete_image(data->mlx, numbers_img[2]);
}