/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:22:20 by crocha-s          #+#    #+#             */
/*   Updated: 2024/12/02 17:07:55 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	end_game(t_game *game)
{
	int	i;

	i = -1;
	free_structs(game);
	i = -1;
	while (++i < 4)
		mlx_destroy_image(game->mlx, game->render[i].image.img_ptr);
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(EXIT_SUCCESS);
}

int	ft_keypress(int keycode, t_game *game)
{
	game->key = keycode;
	if (game->key == ESC)
		end_game(game);
	if (game->key == W)
		game->player->movement.y = 1;
	if (game->key == S)
		game->player->movement.y = -1;
	if (game->key == A)
		game->player->movement.x = -1;
	if (game->key == D)
		game->player->movement.x = 1;
	if (game->key == LEFT)
		game->player->angle = -1;
	if (game->key == RIGHT)
		game->player->angle = 1;
	return (EXIT_SUCCESS);
}

int	ft_keyrelease(int keycode, t_game *game)
{
	game->key = keycode;
	if (game->key == W || game->key == S)
		game->player->movement.y = 0;
	if (game->key == A || game->key == D)
		game->player->movement.x = 0;
	if (game->key == LEFT || game->key == RIGHT)
		game->player->angle = 0;
	return (EXIT_SUCCESS);
}

// static void	my_key_hook(mlx_key_data_t keydata, void *param)
// {
// 	t_game	*game;

// 	game = param;
// 	if (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS)
// 	{
// 		if (keydata.key == MLX_KEY_W)
// 			game->player->movement.y = 1;
// 		if (keydata.key == MLX_KEY_A)
// 		game->player->movement.y = -1;
// 		if (keydata.key == MLX_KEY_S)
// 			game->player->movement.x = -1;
// 		if (keydata.key == MLX_KEY_D)
// 			game->player->movement.x = 1;
// 		if (keydata.key == MLX_KEY_LEFT)
// 			game->player->angle = -1;
// 		if (keydata.key == MLX_KEY_RIGHT)
// 			game->player->angle = 1;
// 	}
// 	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
// 		end_game(game);
// }