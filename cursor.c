#include "cub3D.h"

void load_cursor(t_data *data)
{
    mlx_texture_t *texture;
    mlx_image_t *image;

    texture = mlx_load_png("textures/cursor.png");
    if(!texture)
        exit(1);
    image = mlx_texture_to_image(data->mlx, texture);
    mlx_resize_image(image, 26, 26);
    data->mouse.cursor = image;
    mlx_delete_texture(texture);
}

void draw_cursor(t_data *data)
{
   
    for(int i = 0;i < data->mouse.cursor->width;i++)
    {
        for(int j = 0;j < data->mouse.cursor->height;j++){
            unsigned pixel = get_pixel(data->mouse.cursor, i, j);
            if(pixel)
                mlx_put_pixel(data->img, i+500-13, WINDOWW/2+j+202, pixel);}
    }
}