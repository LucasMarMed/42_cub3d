/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:23:23 by crocha-s          #+#    #+#             */
/*   Updated: 2024/12/02 17:08:00 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_textures(t_game *game)
{
	game->render[0] = set_images(game, game->map->no_texture);
	game->render[1] = set_images(game, game->map->so_texture);
	game->render[2] = set_images(game, game->map->we_texture);
	game->render[3] = set_images(game, game->map->ea_texture);
}

void	init_structs(t_game *game)
{
	*game = (t_game){0};
	game->map = malloc(sizeof(t_map));
	memset(game->map, 0, sizeof(t_map));
	game->player = (t_player *)malloc(sizeof(t_player));
	memset(game->player, 0, sizeof(t_player));
	memset(&game->ray, 0, sizeof(t_rays));
	game->ray.hit_vertical = false;
	game->texture = (t_render *)malloc(sizeof(t_render));
	memset(game->texture, 0, sizeof(t_render));
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_print_err("Invalid arguments: try ./cub3d <path to map>."));
	argv++;
	init_structs(&game);
	if (check_and_parse(&game, argv) == 0)
	{
		game.mlx = mlx_init();
		init_textures(&game);
		game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3d");
		mlx_hook(game.win, DestroyNotify, ButtonPressMask, end_game, &game);
		mlx_hook(game.win, KeyPress, KeyPressMask, ft_keypress, &game);
		mlx_hook(game.win, KeyRelease, KeyReleaseMask, ft_keyrelease, &game);
		ft_init_player_pos(&game);
		mlx_loop_hook(game.mlx, make_game, &game);
		mlx_loop(game.mlx);
	}
	free_structs(&game);
	return (0);
}
