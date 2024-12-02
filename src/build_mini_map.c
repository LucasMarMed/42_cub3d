// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   build_mini_map.c                                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/11/28 00:47:31 by lumarque          #+#    #+#             */
// /*   Updated: 2024/11/28 00:56:20 by lumarque         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../include/cub3d.h"

enum
{
	DOOR_TOGGLING = 95,
	DOOR_OPENED,
	DOOR_CLOSED,
	PLAYER,
	ENEMY_WALK,
	ENEMY_DAMAGED,
	ENEMY_ATTACK,
	ENEMY_DEATH,
};


typedef struct s_draw_minimap
{
	float		center_x;
	float		center_y;
	float		radius_x;
	float		radius_y;
	float		world_x;
	float		world_y;
	int			factor;
	bool		top;
	bool		bottom;
	bool		left;
	bool		right;
	t_iterators	it;
}	t_draw_minimap;

static void	put_color(t_game *g, t_draw_minimap *s, int color)
{
	pixel_put(g, s->center_x + s->it.j - s->radius_x,
		s->center_y + s->it.i - s->radius_y, color);
}

static void	map_check_walls(t_game *g, t_draw_minimap *s)
{
	s->top = ((!has_wall_at(g, s->world_x, s->world_y - s->factor)
				|| has_door_at(g, s->world_x, s->world_y - s->factor))
			&& !has_void_at(g, s->world_x, s->world_y - s->factor));
	s->bottom = ((!has_wall_at(g, s->world_x, s->world_y + s->factor)
				|| has_door_at(g, s->world_x, s->world_y + s->factor))
			&& !has_void_at(g, s->world_x, s->world_y + s->factor));
	s->left = ((!has_wall_at(g, s->world_x - s->factor, s->world_y)
				|| has_door_at(g, s->world_x - s->factor, s->world_y))
			&& !has_void_at(g, s->world_x - s->factor, s->world_y));
	s->right = ((!has_wall_at(g, s->world_x + s->factor, s->world_y)
				|| has_door_at(g, s->world_x + s->factor, s->world_y))
			&& !has_void_at(g, s->world_x + s->factor, s->world_y));
}

static bool	is_door_closed(t_game *g, t_draw_minimap *s)
{
	int		x;
	int		y;

	x = (int)(s->world_x / 64);
	y = (int)(s->world_y / 64);
	return (g->map.arr[y][x] == DOOR_CLOSED);
}

static void	draw_x_radius(t_game *g, t_draw_minimap *s)
{
	while (++s->it.j <= s->radius_x * 2)
	{
		if (s->it.i == 0 || s->it.j == 0
			|| s->it.i == s->radius_y * 2 || s->it.j == s->radius_x * 2)
			put_color(g, s, 0xFFFFFF);
		else
		{
			s->world_x = g->player.pos.x + s->factor * (s->it.j - s->radius_x);
			s->world_y = g->player.pos.y + s->factor * (s->it.i - s->radius_y);
			if (has_void_at(g, s->world_x, s->world_y))
				put_color(g, s, 0x000000);
			else if (is_door_closed(g, s))
				put_color(g, s, 0x003300);
			else if (has_wall_at(g, s->world_x, s->world_y))
			{
				map_check_walls(g, s);
				if (s->top || s->bottom || s->left || s->right)
					put_color(g, s, 0xFFFFFF);
				else
					put_color(g, s, 0x000000);
			}
		}
	}
}

void	draw_minimap(t_game *g)
{
	t_draw_minimap	s;

	s.center_x = WIDTH - 100 - 5;
	s.center_y = 105;
	s.radius_x = 100;
	s.radius_y = 100;
	s.factor = 3;
	s.it.i = -1;
	while (++s.it.i <= s.radius_y * 2)
	{
		s.it.j = -1;
		draw_x_radius(g, &s);
	}
	s.it.i = -1;
	while (++s.it.i < PLAYER_MINIMAP_HEIGHT)
	{
		s.it.j = -1;
		while (++s.it.j < PLAYER_MINIMAP_WIDTH)
			pixel_put(g, s.center_x + s.it.j - PLAYER_MINIMAP_WIDTH / 2,
				s.center_y + s.it.i - PLAYER_MINIMAP_HEIGHT / 2, 0xFF0000);
	}
}