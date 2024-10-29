/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:13:02 by lumarque          #+#    #+#             */
/*   Updated: 2024/10/04 16:13:02 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_variables_valid(t_validate *valid)
{
	valid->invalid = 0;
	valid->player = 0;
}

void	init_data(t_cub *game)
{
	game->data->size_textures = 0;
	game->data->no = NULL;
	game->data->so = NULL;
	game->data->we = NULL;
	game->data->ea = NULL;
	game->data->map = NULL;
	game->data->y_player = 0;
	game->data->x_player = 0;
	game->data->colors = false;
	game->data->floor = 0;
	game->data->ceiling = 0;
}
void	init_cub(t_cub *game)
{
	game->mlx = NULL;
	game->frame_time = 0;
	game->keys.w = false;
	game->keys.s = false;
	game->keys.a = false;
	game->keys.d = false;
	game->keys.left = false;
	game->keys.right = false;
	game->north = NULL;
	game->south = NULL;
	game->west = NULL;
	game->east = NULL;
	game->data = ft_calloc(1, sizeof(t_data));
	init_data(game);
	get_game(game);
}

void	handle_mlx_actions(int action, t_cub *game)
{
	if (action == INIT)
	{
		mlx_set_setting(MLX_STRETCH_IMAGE, true);
		game->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
		if (!game->mlx)
			handle_error("Error: mlx_init failed.");
	}
	else if (action == NEW_IMAGE)
	{
		game->mlx_image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		if (!game->mlx_image)
			handle_error("Error open window.\n");
		if (mlx_image_to_window(game->mlx, game->mlx_image, 0, 0) < 0)
			handle_error("Error mlx_image_to_window.\n");
	}
}

int	init_game(t_cub *game)
{
	handle_mlx_actions(INIT, game);
	handle_mlx_actions(NEW_IMAGE, game);
	load_textures(game);
	setup(game);
	mlx_key_hook(game->mlx, hook_key_press, game);
	mlx_loop_hook(game->mlx, draw_playerview, game);
	mlx_close_hook(game->mlx, hook_close, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_cub	game;

	init_cub(&game);
	validate_map(argc, argv, &game);
	init_game(&game);
	return (EXIT_SUCCESS);
}
