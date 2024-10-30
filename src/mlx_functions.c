/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:36:08 by lumarque          #+#    #+#             */
/*   Updated: 2024/10/30 01:19:18 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	my_key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*data;

	data = param;
	if (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_W)
			move_up(data);
		if (keydata.key == MLX_KEY_A)
			move_left(data);
		if (keydata.key == MLX_KEY_S)
			move_down(data);
		if (keydata.key == MLX_KEY_D)
			move_right(data);
		if (keydata.key == MLX_KEY_LEFT)
			rotate_left(data);
		if (keydata.key == MLX_KEY_RIGHT)
			rotate_right(data);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(data->mlx);
}

static void	fill_main_screen(t_game *data)
{
	float y;
	float x;

	y = -1;
	x = -1;
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
			mlx_put_pixel(data->img->bg, x, y, data->map->c_color);
	}
	y--;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			mlx_put_pixel(data->img->bg, x, y, data->map->f_color);
	}
	mlx_image_to_window(data->mlx, data->img->bg, 0, 0);
}

int	mlx_functions(t_game *data)
{
	if (create_bg_img(data))
		return (1);
	fill_main_screen(data);
	calc_mini_map_scaling(data);
	if (get_textures(data))
		return (1);
	if (get_images(data))
		return (1);
	if (create_ray_img(data))
		return (1);
	if (create_pl_img(data))
		return (1);
	if (data->img->fg)
		mlx_delete_image(data->mlx, data->img->pl);
	if (create_fg_img(data))
		return (1);
	check_init_pl_angle(data);
	draw_fov_3d(data);
	draw_fov(data);
	build_map(data);
	mlx_key_hook(data->mlx, my_key_hook, data);
	mlx_loop(data->mlx);
	return (0);
}