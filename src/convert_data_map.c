/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_data_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:52:08 by crocha-s          #+#    #+#             */
/*   Updated: 2024/12/06 04:40:29 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	parse_color(t_game *game, char **temp, char *trimmed, char *symbol)
{
	int	i;

	i = -1;
	if (!ft_strncmp(trimmed, symbol, 1))
	{
		if (arr_len(temp) != 3)
			return (free_arr(temp), free(trimmed),
				ft_print_err("Error: Floor: wrong color index number."));
		while (temp[++i])
		{
			if (check_alpha(temp[i]) && !ft_strncmp(symbol, "F", 1))
				game->map->floor[i] = -1;
			if (check_alpha(temp[i]) && !ft_strncmp(symbol, "C", 1))
				game->map->ceiling[i] = -1;
			if (!check_alpha(temp[i]) && !ft_strncmp(symbol, "F", 1))
				game->map->floor[i] = ft_atoi(temp[i]);
			if (!check_alpha(temp[i]) && !ft_strncmp(symbol, "C", 1))
				game->map->ceiling[i] = ft_atoi(temp[i]);
		}
	}
	return (0);
}

static int	are_color_valid(t_game *game)
{
	int	i;
	int	*color;
	int	*color2;

	i = 0;
	color = game->map->ceiling;
	while (i < 3)
	{
		if (color[i] > 255 || color[i] < 0)
			return (ft_print_err("Error: Ceiling color index is not valid."));
		i++;
	}
	i = 0;
	color2 = game->map->floor;
	while (i < 3)
	{
		if (color2[i] > 255 || color2[i] < 0)
			return (ft_print_err("Error: Ceiling color index is not valid."));
		i++;
	}
	return (0);
}

static int	read_fc_color(t_game *game, char *line)
{
	char	**temp;
	char	*trimmed;

	trimmed = ft_strtrim(line, " ");
	temp = ft_split(trimmed + 1, ',');
	if (parse_color(game, temp, trimmed, "F")
		|| parse_color(game, temp, trimmed, "C"))
		return (1);
	free_arr(temp);
	game->map->f_color = rgb_to_hex(game->map->floor);
	game->map->c_color = rgb_to_hex(game->map->ceiling);
	free(trimmed);
	return (0);
}

static int	check_duplicates(char **map_arr, int i)
{
	int		counter;
	char	*trimmed;

	counter = 0;
	i = -1;
	while (map_arr[++i])
	{
		trimmed = ft_strtrim(map_arr[i], " ");
		if (!ft_strncmp(trimmed, "NO", 2))
			counter++;
		if (!ft_strncmp(trimmed, "SO", 2))
			counter++;
		if (!ft_strncmp(trimmed, "WE", 2))
			counter++;
		if (!ft_strncmp(trimmed, "EA", 2))
			counter++;
		if (!ft_strncmp(trimmed, "F", 1))
			counter++;
		if (!ft_strncmp(trimmed, "C", 1))
			counter++;
		free(trimmed);
	}
	if (counter != 6)
		return (ft_print_err("Error: Corrupted data."));
	return (0);
}

int	convert_data_map(t_game *game, char *temp_raw_map)
{
	char		**map_arr;
	char		**map_matrix;
	int			i;

	i = 0;
	map_arr = ft_split(temp_raw_map, '\n');
	if (check_duplicates(map_arr, i) != 0 || check_tex_path(game, map_arr) != 0)
		return (free_arr(map_arr), 1);
	while (map_arr[i])
	{
		if (read_fc_color(game, map_arr[i++]) != 0)
			return (free_arr(map_arr), 1);
	}
	free_arr(map_arr);
	map_matrix = ft_split(temp_raw_map, '\n');
	if (are_color_valid(game) != 0 || parse_map_matrix(map_matrix, game) != 0)
		return (free_arr(map_matrix), 1);
	free_arr(map_matrix);
	return (0);
}
