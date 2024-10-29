/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crocha-s <crocha-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:23:23 by crocha-s          #+#    #+#             */
/*   Updated: 2024/10/23 16:28:48 by crocha-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"



void init_structs (t_game *game)
{
	*game = (t_game){0};
	game->map = malloc(sizeof(t_map));
	memset(game->map, 0, sizeof(t_map));
	game->player = (t_player *)malloc(sizeof(t_player));
	memset(game->player, 0, sizeof(t_player));
	
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_print_err("Invalid number of arguments: try ./cub3d <path to map>."));
	argv = argv + 1;
	
	init_structs(&game); //INICIE SUAS VARIAVEIS AQUI
	
		
	
	
	if (check_and_parse(&game, argv) == 0)
	{
		//RENDER VEM A PARTIR DAQUI	
	}
	free_structs(&game); //ADICIONE SEUS FREES AQUI NESTA FUNÇÃO
	
	
	return (0);
}
