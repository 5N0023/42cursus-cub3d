#include "cub3D.h"


int checkduplicate(t_data *data, double x, double y)
{
    t_spritelist *tmp;

    tmp = data->ray.spritelist;
    while (tmp != NULL)
    {
        if (tmp->spritehitx == x && tmp->spritehity == y)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

void add_back_to_sprites(t_data *data, double x, double y,int side)
{
    t_spritelist *new;
    t_spritelist *last;

    if (checkduplicate(data, x, y) == 1)
    {
        printf("Error\nDuplicate sprite\n");
        return;
    }
    new = malloc(sizeof(t_spritelist));
    new->xstart = -1;
    new->spritehitx = x+0.5;
    new->spritehity = y+0.5;
    new->spritehitside = side;
    new->spritedistance = sqrtf(pow(data->player.x - new->spritehitx, 2) + pow(data->player.y - new->spritehity, 2));
    new->next = NULL;
    if (data->ray.spritelist == NULL)
    {
        data->ray.spritelist = new;
        return;
    }
    last = data->ray.spritelist;
    while (last->next != NULL)
        last = last->next;
    last->next = new;
}

void reverse_sprites_list(t_data *data)
{
    t_spritelist *prev;
    t_spritelist *current;
    t_spritelist *next;

    prev = NULL;
    current = data->ray.spritelist;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next; 
    }
    data->ray.spritelist = prev;
}
static void swap(t_spritelist *a, t_spritelist *b)
{
    t_spritelist tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
void free_sprites_list(t_data *data)
{
    t_spritelist *tmp;
    t_spritelist *tmp2;

    tmp = data->ray.spritelist;
    while (tmp != NULL)
    {
        tmp2 = tmp->next;
        free(tmp);
        tmp = tmp2;
    }
    data->ray.spritelist = NULL;
}

void sort_sprites(t_data *data, int reverse)
{
    t_spritelist *tmp;
    
    tmp = data->ray.spritelist;
    while (tmp != NULL)
    {
        if (tmp->next != NULL && tmp->spritedistance > tmp->next->spritedistance)
        {
            swap(tmp, tmp->next);
            tmp = data->ray.spritelist;
        }
        else
            tmp = tmp->next;
    }
    if (reverse)
        reverse_sprites_list(data);
}


void sprite_textures(t_data *data)
{
    mlx_texture_t *texture;
    int i;

    i = 0;
    data->texture.sprite = malloc(sizeof(mlx_image_t*) * 29);
    char path2[50] = "textures/sprite/frame_00.png";
    while(i < 29)
    {
        path2[22] = (i+1) / 10 + '0';
        path2[23] = (i+1) % 10 + '0';
        texture = mlx_load_png(path2);
        if(!texture)
            exit(1);
        data->texture.sprite[i] = mlx_texture_to_image(data->mlx, texture);
        mlx_resize_image(data->texture.sprite[i] , 250, 250);
        mlx_delete_texture(texture);
        i++;
    }
}