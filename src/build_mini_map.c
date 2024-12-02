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

// /*Populates texture variables, texture struct itself is already initialised
//   within init_game function.*/
// int	get_textures(t_game *game)
// {
// 	game->txtr->wl = mlx_load_png("./textures/black_wall_mini_map.png");
// 	if (!game->txtr->wl)
// 		return (1);
// 	game->txtr->fl = mlx_load_png("./textures/white_floor_mini_map.png");
// 	if (!game->txtr->fl)
// 		return (1);
// 	return (0);
// }

// /*Populates image variables, image struct itself is already initialised
//   within init_game function.*/
// int	get_images(t_game *game)
// {
// 	game->img->wl = mlx_texture_to_image(game->mlx, game->txtr->wl);
// 	if (!game->img->wl)
// 		return (1);
// 	game->img->fl = mlx_texture_to_image(game->mlx, game->txtr->fl);
// 	if (!game->img->fl)
// 		return (1);
// 	mlx_resize_image(game->img->wl, game->PX, game->PX);
// 	mlx_resize_image(game->img->fl, game->PX, game->PX);
// 	return (0);
// }

// /*Initialises variables of the player struct used in draw_player function.*/
// static void	init_pl(t_pl *pl)
// {
// 	pl->x_strt = 0;
// 	pl->y_strt = 0;
// 	pl->pix_x = -1;
// 	pl->pix_y = -1;
// 	pl->fnl_x = 0;
// 	pl->fnl_y = 0;
// }

// /*-strt: calculates starting position of player
//   -fnl: translates pixel back to original position, uses round
//    function for better accuracy*/
// void	draw_player(t_game *game, float width, float height)
// {
//     t_pl	pl;

// 	init_pl(&pl);
// 	pl.x_strt = (game->x_p * game->PX);
// 	pl.y_strt = (game->y_p * game->PX);
// 	while (++pl.pix_y <= height)
// 	{
// 		pl.pix_x = -1;
// 		while (++pl.pix_x <= width)
// 		{
// 			pl.fnl_x = round(pl.x_strt + pl.pix_x);
// 			pl.fnl_y = round(pl.y_strt + pl.pix_y);

// 			if (pl.fnl_x >= 0 && pl.fnl_x < game->width * game->PX
// 				&& pl.fnl_y >= 0 && pl.fnl_y < game->height * game->PX)
// 			{
// 				mlx_put_pixel(game->img->pl, pl.fnl_x, pl.fnl_y, 0x00FF00FF);
// 				mlx_image_to_window(game->mlx, game->img->pl, 0, 0);
// 			}
// 		}
// 	}
// }

// /*Builds 2d minimap (floor, wall, player).*/
// void	build_map(t_game *game)
// {
// 	int		y;
// 	int		x;

// 	y = -1;
// 	x = -1;

// 	base_map(game);
// 	get_images(game);
// 	create_pl_img(game);
// 	while (game->map[++y])
// 	{
// 		x = -1;
// 		while (game->map[y][++x])
// 		{
// 			mlx_image_to_window(game->mlx, game->img->fl, x * game->PX, y * game->PX);
// 			if (game->map[y][x] == '1')
// 				mlx_image_to_window(game->mlx, game->img->wl, x * game->PX, y * game->PX);
// 		}
// 	}
// 	game->pl_size = game->PX / MM_SIZE / 2;
// 	draw_player(game, game->pl_size, game->pl_size);
// }
