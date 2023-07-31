#include"cub3D.h"


int get_door_frame(t_data *data)
{
    for(int i = 0;i < data->map.doors_count;i++)
    {
        if(data->map.doors[i].x == (int)data->ray.doorhitx && data->map.doors[i].y == (int)data->ray.doorhity)
            return (data->map.doors[i].frame);
    }
    return (0);
}

int door_state(t_data *data, int x, int y)
{
    for(int i = 0;i < data->map.doors_count;i++)
    {
        if(data->map.doors[i].x == x && data->map.doors[i].y == y)
        {
            return (data->map.doors[i].state);
        }
    }
    return (0);
}


void door_textures(t_data *data)
{
    mlx_texture_t *texture;
    data->texture.door = malloc(sizeof(mlx_image_t*) * 35);
    char path2[50] = "textures/door/frame-000.png";
    for(int i = 0;i < 35;i++)
    {
        path2[21] = (i+1) / 10 + '0';
        path2[22] = (i+1) % 10 + '0';
        texture = mlx_load_png(path2);
        data->texture.door[i] = mlx_texture_to_image(data->mlx, texture);
        mlx_resize_image(data->texture.door[i] , 250, 250);
        mlx_delete_texture(texture);
    }
}

void door_frames_setter(t_data *data)
{
    for(int i = 0;i < data->map.doors_count;i++)
    {
       if(data->map.doors[i].state == CLOSED)
            data->map.doors[i].frame = 0;
        else if(data->map.doors[i].state == OPENING)
            data->map.doors[i].frame++;
        else if(data->map.doors[i].state == OPENED)
            data->map.doors[i].frame = 34;
        else if(data->map.doors[i].state == CLOSING)
            data->map.doors[i].frame--;
        if (data->map.doors[i].frame <= 0)
        {
            data->map.doors[i].frame = 0;
            data->map.doors[i].state = CLOSED;
        }
        if (data->map.doors[i].frame > 34)
        {
            data->map.doors[i].frame = 34;
            data->map.doors[i].state = OPENED;
        }

    }
}

void door_frames_contorller(t_data *data)
{
    hits(data->player.angle,data);
    if (data->ray.doorhit == 1)
    {
    for(int i = 0;i < data->map.doors_count;i++)
    {
        if (data->map.doors[i].x == (int)data->ray.doorhitx && data->map.doors[i].y == (int)data->ray.doorhity && data->ray.doordistance < 3 && data->ray.doordistance > 0.2)
       {
        if (data->map.doors[i].state == OPENING)
            data->map.doors[i].state = CLOSING;
       else if (data->map.doors[i].state == CLOSING)
            data->map.doors[i].state = OPENING;
        else if (data->map.doors[i].state == CLOSED)
            data->map.doors[i].state = OPENING;
        else if (data->map.doors[i].state == OPENED)
            data->map.doors[i].state = CLOSING;
            }
    }
    }
}