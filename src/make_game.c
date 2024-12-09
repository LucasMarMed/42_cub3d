/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:30:18 by crocha-s          #+#    #+#             */
/*   Updated: 2024/12/09 16:31:56 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	make_game(t_game *cub3d)
{
	if (cub3d->key)
		movements(cub3d);
	generate_image(cub3d);
	raycast(cub3d);
	return (EXIT_SUCCESS);
}
