#include "cub3D.h"

void draw_cursor(t_data *data)
{
    mlx_texture_t *texture;
    mlx_image_t *image;
    texture = mlx_load_png("textures/cursor.png");
    image = mlx_texture_to_image(data->mlx, texture);
    mlx_resize_image(image, 26, 26);
    for(int i = 0;i < image->width;i++)
    {
        for(int j = 0;j < image->height;j++){
            unsigned pixel = get_pixel(image, i, j);
            if(pixel)
                mlx_put_pixel(data->img, i+500-13, WINDOWW/2+j+150, pixel);}
    }
    mlx_delete_texture(texture);
    mlx_delete_image(data->mlx, image);
}