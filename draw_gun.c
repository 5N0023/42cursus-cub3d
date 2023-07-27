

void draw_gun(t_data *data)
{
	static int f ;
	static int reverse;
	static int  k ;
	if(data->player.gun.state == 0)
	{
		f = 15;
		for(int i = 0;i < data->player.gun.gunreload[k/2]->width;i++)
			{
				int s= 0;
				int skip = 0;
				for(int j = 0;j < data->player.gun.gunreload[k/2]->height;j++){
					unsigned pixel = get_pixel(data->player.gun.gunreload[k/2], i, j);
					if (g < 210)
					{
						if (s <2)
						{
							s++;
							continue;
						}
						mlx_put_pixel(data->img, i, j+(WINDOWW - data->player.gun.gunreload[k/2]->height), pixel);}
					}
			}
		if (reverse == 1)
			k--;
		else
			k++;
		if (k < 0 && reverse == 1)
		{
			k = 0;
			reverse = 0;
		}
		if (k == 10*2 && reverse == 0)
		{
			reverse = 1;
			k = 9*2;
		}
		
	}
	if (data->player.gun.state == 2)
	{
		for(int i = 0;i < data->player.gun.gunreload[f/2]->width;i++)
			{
				int s= 0;
				int skip = 0;
				for(int j = 0;j < data->player.gun.gunreload[f/2]->height;j++){
					unsigned pixel = get_pixel(data->player.gun.gunreload[f/2], i, j);
					uint8_t r = pixel >> 24;
					uint8_t g = pixel >> 16;
					uint8_t b = pixel >> 8;
					uint8_t a = pixel;
					if (g < 210)
					{
						if (s <2)
						{
							s++;
							continue;
						}
						mlx_put_pixel(data->img, i, j+(WINDOWW - data->player.gun.gunreload[f/2]->height), pixel);}
					}
			}
		f++;
		if (f == 100*2)
		{
			f = 15;
			data->player.gun.state = 0;
		}
	}
}