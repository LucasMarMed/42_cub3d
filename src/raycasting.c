/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:20:18 by lumarque          #+#    #+#             */
/*   Updated: 2024/12/09 16:35:41 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ray_intersections(t_game *game)
{
	if (game->ray.direction.x < 0)
	{
		game->ray.map_mov.x = -1;
		game->ray.intersection.x = (game->player->pos.x
				- game->ray.map.x) * game->ray.delta.x;
	}
	else
	{
		game->ray.map_mov.x = 1;
		game->ray.intersection.x = (game->ray.map.x + 1
				- game->player->pos.x) * game->ray.delta.x;
	}
	if (game->ray.direction.y < 0)
	{
		game->ray.map_mov.y = -1;
		game->ray.intersection.y = (game->player->pos.y
				- game->ray.map.y) * game->ray.delta.y;
	}
	else
	{
		game->ray.map_mov.y = 1;
		game->ray.intersection.y = (game->ray.map.y + 1
				- game->player->pos.y) * game->ray.delta.y;
	}
}

void	ray_setup(t_game *game, int pixel)
{
	double	multiplier;

	multiplier = 2 * pixel / (double)WIDTH - 1;
	game->ray.direction.x = game->player->dir.x
		+ game->player->plane.pos.x * multiplier;
	if (game->ray.direction.x == 0)
		game->ray.delta.x = 1e30;
	else
		game->ray.delta.x = fabs(1 / game->ray.direction.x);
	game->ray.direction.y = game->player->dir.y
		+ game->player->plane.pos.y * multiplier;
	if (game->ray.direction.y == 0)
		game->ray.delta.y = 1e30;
	else
		game->ray.delta.y = fabs(1 / game->ray.direction.y);
	game->ray.map.x = (int)game->player->pos.x;
	game->ray.map.y = (int)game->player->pos.y;
	ray_intersections(game);
}

void	dda(t_game *game)
{
	int	hit_flag;

	hit_flag = false;
	while (!hit_flag)
	{
		if (game->ray.intersection.x < game->ray.intersection.y)
		{
			game->ray.intersection.x += game->ray.delta.x;
			game->ray.map.x += game->ray.map_mov.x;
			game->ray.hit_vertical = true;
		}
		else
		{
			game->ray.intersection.y += game->ray.delta.y;
			game->ray.map.y += game->ray.map_mov.y;
			game->ray.hit_vertical = false;
		}
		if (game->map->map_matrix[(int)game->ray.map.y]
			[(int)game->ray.map.x] == '1')
			hit_flag = true;
	}
}

void	distance_to_the_wall(t_game *game)
{
	if (game->ray.hit_vertical == true)
		game->ray.perp_wall_dist = (game->ray.intersection.x
				- game->ray.delta.x);
	else
		game->ray.perp_wall_dist = (game->ray.intersection.y
				- game->ray.delta.y);
	if (game->ray.perp_wall_dist < 0.0001)
		game->ray.perp_wall_dist = 0.0001;
	game->img_info.line_height = fabs((HEIGHT / game->ray.perp_wall_dist));
	game->img_info.draw_start = HEIGHT / 2 - game->img_info.line_height / 2;
	if (game->img_info.draw_start < 0)
		game->img_info.draw_start = 0;
	game->img_info.draw_end = HEIGHT / 2 + game->img_info.line_height / 2;
	if (game->img_info.draw_end >= HEIGHT)
		game->img_info.draw_end = HEIGHT;
	game->img_info.scale = SPRITE_SIZE / game->img_info.line_height;
	game->img_info.pos_texture = (game->img_info.draw_start - (int)HEIGHT / 2
			+ game->img_info.line_height / 2) * game->img_info.scale;
}

void	raycast(t_game *game)
{
	int	pixel;

	pixel = -1;
	game->ray.hit_vertical = false;
	while (++pixel <= ((int)WIDTH - 1))
	{
		ray_setup(game, pixel);
		dda(game);
		distance_to_the_wall(game);
		texture_calc(game);
		ft_putcolor(game, pixel, 'c');
		ft_textures(game, pixel);
		ft_putcolor(game, pixel, 'f');
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	mlx_destroy_image(game->mlx, game->img.img_ptr);
}
