/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:06:26 by crocha-s          #+#    #+#             */
/*   Updated: 2024/12/02 17:07:42 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	size_of_file(int fd, char *buffer, int read_bytes)
{
	int		counter;

	counter = 0;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, 1);
		if (read_bytes < 0)
		{
			close(fd);
			return (1);
		}
		counter++;
	}
	return (counter);
}

static char	*read_content(int fd, char *content, int counter, char *path)
{
	int	read_bytes;

	read_bytes = 1;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	read_bytes = read(fd, content, counter);
	if (read_bytes < 0)
	{
		close(fd);
		return (NULL);
	}
	return (content);
}

static char	*read_map_file(char **path)
{
	char	buffer[1024];
	char	*content;
	int		fd;
	int		read_bytes;
	int		counter;

	counter = 0;
	fd = open(*path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	read_bytes = 1;
	counter = size_of_file(fd, buffer, read_bytes);
	if (counter == 0)
		return (NULL);
	content = (char *)malloc(counter * sizeof(char));
	if (!content)
		return (NULL);
	content[counter - 1] = '\0';
	close(fd);
	content = read_content(fd, content, counter, *path);
	close(fd);
	return (content);
}

int	check_and_parse(t_game *game, char **path)
{
	char	*temp_raw_map;
	int		len;

	len = ft_strlen(*path);
	if (ft_strncmp(*path + len - 4, ".cub", 4))
		return (ft_print_err("Error: File is not a .cub format."));
	game->file = *path;
	temp_raw_map = read_map_file(path);
	if (temp_raw_map == NULL)
		return (1);
	if (convert_data_map(game, temp_raw_map) != 0)
	{
		free(temp_raw_map);
		return (1);
	}
	free(temp_raw_map);
	return (0);
}
