#include"cub3D.h"


int get_door_frame(t_doorlist *tmp,t_data *data)
{
    int i;

    i = 0;
    while(i < data->map.doors_count)
    {
        if(data->map.doors[i].x == (int)tmp->doorhitx && data->map.doors[i].y == (int)tmp->doorhity)
            return (data->map.doors[i].frame);
        i++;
    }
    return (0);
}

int door_state(t_data *data, int x, int y)
{
    int i;

    i = 0;
    while(i < data->map.doors_count)
    {
        if(data->map.doors[i].x == x && data->map.doors[i].y == y)
        {
            return (data->map.doors[i].state);
        }
        i++;
    }
    return (0);
}


void door_textures(t_data *data)
{
    mlx_texture_t *texture;
    int i;

    i = 0;
    data->texture.door = malloc(sizeof(mlx_image_t*) * 35);
    char path2[50] = "textures/door/frame-000.png";
    while(i < 35)
    {
        path2[21] = (i+1) / 10 + '0';
        path2[22] = (i+1) % 10 + '0';
        texture = mlx_load_png(path2);
        if(!texture)
            exit(1);
        data->texture.door[i] = mlx_texture_to_image(data->mlx, texture);
        mlx_resize_image(data->texture.door[i] , 250, 250);
        mlx_delete_texture(texture);
        i++;
    }
}

void door_frames_setter(t_data *data)
{
    int i;

    i = 0;
    while(i < data->map.doors_count)
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
        i++;
    }
}

void free_door_list(t_data *data)
{
    t_doorlist *tmp;
    t_doorlist *tmp2;

    tmp = data->ray.doorlist;
    if(!tmp)
        return;
    while (tmp != NULL)
    {
        tmp2 = tmp->next;
        free(tmp);
        tmp = tmp2;
    }
    data->ray.doorlist = NULL;
}

void door_frames_controller(t_data *data)
{
    t_doorlist *tmp;
    int i = 0;

    hits(data->player.angle,data);
    tmp = data->ray.doorlist;
    if (tmp)
        while(tmp->next)
            tmp = tmp->next;
    if(!tmp)
    {
        free_door_list(data);
        return;
    }
    if (tmp)
    {
   while(i < data->map.doors_count)
    {
        if (data->map.doors[i].x == (int)tmp->doorhitx && data->map.doors[i].y == (int)tmp->doorhity && tmp->doordistance < 3 && tmp->doordistance > 0.15)
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
        i++;
    }
    }
    free_door_list(data);
}

void add_back_to_doors(t_data *data, double x, double y,int side)
{
    t_doorlist *new;
    t_doorlist *last;

    new = malloc(sizeof(t_doorlist));
    new->doorhitx = x;
    new->doorhity = y;
    new->doorhitside = side;
    new->doordistance = sqrtf(pow(data->player.x - x, 2) + pow(data->player.y - y, 2));
    new->next = NULL;
    if (data->ray.doorlist == NULL)
    {
        data->ray.doorlist = new;
        return;
    }
    last = data->ray.doorlist;
    while (last->next != NULL)
        last = last->next;
    last->next = new;
}

static void swap(t_doorlist *a, t_doorlist *b)
{
    t_doorlist tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverse_door_list(t_data *data)
{
    t_doorlist *prev;
    t_doorlist *current;
    t_doorlist *next;

    prev = NULL;
    current = data->ray.doorlist;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next; 
    }
    data->ray.doorlist = prev;
}

void sort_door_list(t_data *data, int reverse)
{
    if (reverse)
        reverse_door_list(data);
}

