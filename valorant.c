#include "cub3D.h"

void valorant_mode(t_data *data)
{
    static int reverse = 0;
    if(!reverse)
    {
        for(int i = 0;i < data->player.gun.valorant.ult[data->player.gun.valorant.ultiframe]->width;i++)
	{
     for(int j = 0;j < data->player.gun.valorant.ult[data->player.gun.valorant.ultiframe]->height;j++){
        unsigned pixel = get_pixel(data->player.gun.valorant.ult[data->player.gun.valorant.ultiframe], i, j);
        if ((uint8_t)pixel)
        {
            mlx_put_pixel(data->img, i, j+(WINDOWW -data->player.gun.valorant.ult[data->player.gun.valorant.ultiframe]->height), pixel);}
        }
	}
    data->player.gun.valorant.ultiframe++;
    }
    else 
        {
            for(int i = 0;i < data->player.gun.valorant.ult[data->player.gun.valorant.ultiframe]->width;i++)
	{
     for(int j = 0;j < data->player.gun.valorant.ult[data->player.gun.valorant.ultiframe]->height;j++){
        unsigned pixel = get_pixel(data->player.gun.valorant.ult[data->player.gun.valorant.ultiframe], i, j);
        if ((uint8_t)pixel)
            mlx_put_pixel(data->img, i, j+(WINDOWW -data->player.gun.valorant.ult[data->player.gun.valorant.ultiframe]->height), pixel);}
	}
    data->player.gun.valorant.ultiframe--;
        }
    if(data->player.gun.valorant.knifes == 5)
    {
        if(data->player.gun.valorant.ultiframe == 32)
            reverse = 1;
        else if (data->player.gun.valorant.ultiframe <28)
         reverse = 0;
    }
    else if(data->player.gun.valorant.knifes == 4)
    {
     if(data->player.gun.valorant.ultiframe == 54)
        reverse = 1;
     else if (data->player.gun.valorant.ultiframe < 50)
         reverse = 0;
    }
    else if(data->player.gun.valorant.knifes == 3)
    {
     if(data->player.gun.valorant.ultiframe == 86)
        reverse = 1;
     else if (data->player.gun.valorant.ultiframe < 84)
         reverse = 0;
    }
    else if(data->player.gun.valorant.knifes == 2)
    {
     if(data->player.gun.valorant.ultiframe == 112)
        reverse = 1;
     else if (data->player.gun.valorant.ultiframe < 108)
         reverse = 0;
    }
    else if(data->player.gun.valorant.knifes == 1)
    {
     if(data->player.gun.valorant.ultiframe == 135)
        reverse = 1;
     else if (data->player.gun.valorant.ultiframe < 130)
         reverse = 0;
    }
    else{
        data->player.gun.valorant.knifes = 5;
        reverse = 0;
    }
    if (data->player.gun.valorant.ultiframe == 139)
        data->player.gun.valorant.ultiframe = 0;
    if (data->mouse.click == 1)
    {
        data->player.gun.valorant.knifes--;
        data->mouse.click = 0;
    }
}