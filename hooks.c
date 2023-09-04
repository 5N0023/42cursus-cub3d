#include "cub3D.h"

void	hooks_handler(mlx_key_data_t key, t_data *data)
{
	if (key.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.angle += 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.angle -= 1;
	if (key.key == MLX_KEY_S && key.action == MLX_PRESS)
		data->player.spress = 1;
	if (key.key == MLX_KEY_S && key.action == MLX_RELEASE)
		data->player.spress = 0;
	if (key.key == MLX_KEY_W && key.action == MLX_PRESS)
		data->player.wpress = 1;
	if (key.key == MLX_KEY_W && key.action == MLX_RELEASE)
		data->player.wpress = 0;
	if (key.key == MLX_KEY_D && key.action == MLX_PRESS)
		data->player.dpress = 1;
	if (key.key == MLX_KEY_D && key.action == MLX_RELEASE)
		data->player.dpress = 0;
	if (key.key == MLX_KEY_A && key.action == MLX_PRESS)
		data->player.apress = 1;
	if (key.key == MLX_KEY_A && key.action == MLX_RELEASE)
		data->player.apress = 0;
	if (key.key == MLX_KEY_R && key.action == MLX_PRESS)
		data->player.gun.state = RELOAD;
}
mlx_keyfunc	key_hook(mlx_key_data_t key, t_data *data)
{
	hooks_handler(key, data);
	if (key.key == MLX_KEY_P && key.action == MLX_PRESS && (data->state == GAME
			|| data->state == STARTMENU))
	{
		if (data->state == GAME)
		{
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
			data->state = STARTMENU;
		}
	}
	if (key.key == MLX_KEY_F && key.action == MLX_PRESS)
		door_frames_controller(data);
	return (NULL);
}