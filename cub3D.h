/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:04:20 by mlektaib          #+#    #+#             */
/*   Updated: 2023/09/04 23:19:51 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SPEED 0.1
# define NORD 0
# define WINDOWW 1000
# define SUD 1
# define EAST 2
# define OUEST 3
# define VERTICALE 0
# define HORIZONTALE 1
# define NORMAL 0
# define STARTSCREEN 0
# define STARTMENU 1
# define GAME 2
# define PAUSE 3
# define SHOOT 1
# define RELOAD 2
# define LOOK 3
# define START 4
# define EXIT 1
# define RESUME 2
# define OPTIONS 8
# define NONE 0
# define CLOSED 1
# define OPENED 0
# define OPENING 2
# define CLOSING 3
# define NS 0
# define WE 1
# include "MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "data_types.h"
# include "parsing/includes/parsing.h"

void					load_normal_texture(t_data *data);
unsigned int			get_pixel(mlx_image_t *img, int i, int j);
void					draw_gun_normal(t_data *data);
double					hits(double angle, t_data *data);
void					startscreen(t_data *data);
void					load_loading_texture(t_data *data);
void					startmenu(t_data *data);
void					load_startmenu_texture(t_data *data);
void					draw_cursor(t_data *data);
void					options(t_data *data);
void					load_cursor(t_data *data);
void					render_texture(t_data *data, int x, double wallheight);
void					load_walls_textures(t_data *data);
void					door_textures(t_data *data);
int						door_state(t_data *data, int x, int y);
int						get_door_frame(t_doorlist *tmp, t_data *data);
void					door_frames_setter(t_data *data);
void					door_frames_controller(t_data *data);
void					add_back_to_doors(t_data *data, double x, double y,
							int side);
void					sort_door_list(t_data *data, int reverse);
void					free_door_list(t_data *data);
double					collision(double angle, t_data *data);
void					castrayvertical(t_hit *vhit, t_data *data);
void					castrayhorizontal(t_hit *hhit, t_data *data);
void					draw_map(t_data *data, int size);
mlx_t					*initdefaultval(t_data *data_ptr);
void					game(t_data *data);
void					move_player(t_data *data);
int						ft_pixel(int r, int g, int b, int a);
mlx_keyfunc				key_hook(mlx_key_data_t key, t_data *data);
void					normalize_angle(double *angle);
void					put_mouse_sensitive(t_data *data, mlx_image_t *image);
void					put_number_pos(mlx_image_t *image, mlx_image_t *img,
							int x, int y);
void					put_player_speed(t_data *data, mlx_image_t *image);
void					put_to_dataimg(t_data *data, mlx_image_t *image, int x,
							int y);
void					render_door_we(t_data *data, int x, double wallheight,
							t_doorlist *tmp);
void					render_door_ns(t_data *data, int x, double wallheight,
							t_doorlist *tmp);
mlx_image_t				*get_number_image(char *path, int number, t_data *data);
void					render_ouest(t_data *data, int x, double wallheight);
void					render_east(t_data *data, int x, double wallheight);
void					render_nord(t_data *data, int x, double wallheight);
void					render_sud(t_data *data, int x, double wallheight);
void					draw_wall(mlx_image_t *img, int pixelsline,
							double wallheight, t_data *data);
void					draw_ceil_floor(t_data *data, int x, double wallheight);
void					calcul_num(int numbers[3], double num);
void					swap(t_doorlist *a, t_doorlist *b);
void					door_remote(t_data *data, int i, t_doorlist *tmp);

#endif