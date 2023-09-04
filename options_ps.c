/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_ps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:16:46 by mlektaib          #+#    #+#             */
/*   Updated: 2023/09/04 23:09:50 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	put_numbers(mlx_image_t *image, mlx_image_t *numbers_img[3])
{
	put_number_pos(image, numbers_img[0], 675, 320);
	put_number_pos(image, numbers_img[1], 725, 320);
	put_number_pos(image, numbers_img[2], 775, 320);
}

void	calcul_num(int numbers[3], double num)
{
	int	tmp;

	tmp = (int)(num * 1000);
	numbers[0] = tmp / 100;
	numbers[1] = (tmp / 10) % 10;
	numbers[2] = tmp % 10;
}

void	load_numbers_ps(t_data *data, mlx_image_t *numbers_img[3],
		int numbers[3])
{
	char	*path;

	path = ft_strdup("textures/numbers/0.png");
	numbers_img[0] = get_number_image(path, numbers[0], data);
	numbers_img[1] = get_number_image(path, numbers[1], data);
	numbers_img[2] = get_number_image(path, numbers[2], data);
	free(path);
}

void	put_player_speed(t_data *data, mlx_image_t *image)
{
	mlx_image_t	*numbers_img[3];
	int			numbers[3];

	calcul_num(numbers, data->player.speed);
	load_numbers_ps(data, numbers_img, numbers);
	put_numbers(image, numbers_img);
	mlx_delete_image(data->mlx, numbers_img[0]);
	mlx_delete_image(data->mlx, numbers_img[1]);
	mlx_delete_image(data->mlx, numbers_img[2]);
}
