/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:05:07 by crocha-s          #+#    #+#             */
/*   Updated: 2024/12/06 06:28:51 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_wall_x(t_game *game)
{
	double	wall_x;
	t_rays	*ray;

	ray = &game->ray;
	wall_x = 0;
	game->img_info.tex_x = 0;
	if (ray->hit_vertical == true)
		wall_x = game->player->pos.y + ray->perp_wall_dist * ray->direction.y;
	else
		wall_x = game->player->pos.x + ray->perp_wall_dist * ray->direction.x;
	wall_x -= floor(wall_x);
	game->img_info.tex_x = (int)(wall_x * (int)SPRITE_SIZE);
}

void	get_img_address(t_image *img)
{
	img->address = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	texture_calc(t_game *game)
{
	t_rays	*ray;

	ray = &game->ray;
	game->texture->index = NO;
	ft_wall_x(game);
	if ((ray->hit_vertical == true && ray->direction.x < 0)
		|| (ray->hit_vertical == false && ray->direction.y > 0))
		game->img_info.tex_x = SPRITE_SIZE - game->img_info.tex_x - 1;
	if (ray->hit_vertical == false)
	{
		if (ray->direction.y > 0)
			game->texture->index = SO;
		else
			game->texture->index = NO;
	}
	else if (ray->hit_vertical == true)
	{
		if (ray->direction.x > 0)
			game->texture->index = WE;
		else
			game->texture->index = EA;
	}
}
