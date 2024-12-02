/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:35:48 by crocha-s          #+#    #+#             */
/*   Updated: 2024/12/02 17:07:48 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
	{
		return ;
	}
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_structs(t_game *game)
{
	if (game->map->map_matrix)
		free_arr(game->map->map_matrix);
	free(game->texture);
	if (game->map->no_texture)
		free(game->map->no_texture);
	if (game->map->so_texture)
		free(game->map->so_texture);
	if (game->map->we_texture)
		free(game->map->we_texture);
	if (game->map->ea_texture)
		free(game->map->ea_texture);
	free(game->map);
	free(game->player);
}
