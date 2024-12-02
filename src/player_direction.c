/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:07:29 by crocha-s          #+#    #+#             */
/*   Updated: 2024/12/02 16:49:48 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	player_direction(t_game *game)
{
	int	dir;

	dir = 1;
	if (game->player->fov == 'N')
		game->player->dir = (t_coord){0, -dir};
	else if (game->player->fov == 'S')
		game->player->dir = (t_coord){0, dir};
	else if (game->player->fov == 'W')
		game->player->dir = (t_coord){-dir, 0};
	else if (game->player->fov == 'E')
		game->player->dir = (t_coord){dir, 0};
	game->player->movement = (t_coord){0, 0};
	game->player->plane.pos.x = -game->player->dir.y;
	game->player->plane.pos.y = game->player->dir.x;
}
