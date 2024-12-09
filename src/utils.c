/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:52:22 by crocha-s          #+#    #+#             */
/*   Updated: 2024/12/06 06:20:00 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	arr_len(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	check_alpha(char *line)
{
	char	*str;
	int		i;

	str = line + 1;
	i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == ' ' || str[i] == ',')
		{
			i++;
			continue ;
		}
		else
			return (1);
	}
	return (0);
}

int	rgb_to_hex(int *rgb)
{
	int	color;

	color = (rgb[0] << 16 | rgb[1] << 8
			| rgb[2]);
	return (color);
}

void	ft_perror(char *msg, t_game *game)
{
	int	i;

	i = -1;
	printf("%s", msg);
	if (!game)
		exit (EXIT_FAILURE);
	while (++i < 4)
	{
		if (game->render[i].image.img_ptr)
			mlx_destroy_image(game->mlx, game->render[i].image.img_ptr);
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free (game->mlx);
	}
	if (game->map->map_matrix)
		free_arr(game->map->map_matrix);
	exit (EXIT_SUCCESS);
}
