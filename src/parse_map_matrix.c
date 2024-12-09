/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:42:26 by crocha-s          #+#    #+#             */
/*   Updated: 2024/12/09 16:32:36 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_numbers(int player_count, int garbage)
{
	if (player_count != 1)
		return (ft_print_err("Error: Wrong number of players on map."));
	if (garbage != 0)
		return (ft_print_err("Error: Garbage characters on map."));
	return (0);
}

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
	game->key = 0;
}

static int	get_dir_and_fov(t_game *game, int player_count, int garbage)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	while (game->map->map_matrix[++i])
	{
		j = -1;
		while (game->map->map_matrix[i][++j])
		{
			c = game->map->map_matrix[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player->pos.y = i + (2 * BUFFER_DISTANCE);
				game->player->pos.x = j + (2 * BUFFER_DISTANCE);
				game->player->fov = c;
				game->map->map_matrix[i][j] = '0';
				player_count++;
			}
			else if (c != '0' && c != '1' && c != '#')
				garbage++;
		}
	}
	player_direction(game);
	return (check_numbers(player_count, garbage));
}

int	parse_map_matrix(char **map_line, t_game *game)
{
	int	player_count;
	int	garbage;

	player_count = 0;
	garbage = 0;
	if (flood_fill(map_line + 6, game) != 0)
		return (1);
	return (get_dir_and_fov(game, player_count, garbage));
}
