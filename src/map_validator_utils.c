/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:14:33 by ruiferna          #+#    #+#             */
/*   Updated: 2025/06/13 07:39:02 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	validate_map(t_game *game)
{
	if (!check_map_walls(game))
		return (0);
	if (!check_map_elements(game))
		return (0);
	if (!check_path_validity(game))
		return (0);
	return (1);
}

int	check_map_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if ((i == 0 || i == game->map_height - 1 || j == 0
					|| j == game->map_width - 1) && game->map[i][j] != WALL)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map_elements(t_game *game)
{
	int	i;
	int	j;
	int	players;
	int	exits;

	players = 0;
	exits = 0;
	game->collectibles = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == PLAYER)
				players++;
			else if (game->map[i][j] == EXIT)
				exits++;
			else if (game->map[i][j] == COLLECTIBLE)
				game->collectibles++;
			j++;
		}
		i++;
	}
	return (players == 1 && exits == 1 && game->collectibles >= 1);
}

static char	**read_map_lines(int fd, t_game *game)
{
	char	*line;
	char	**map;
	int		i;

	map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map[i] = line;
		if (i++ == 0)
			game->map_width = ft_strlen(line);
	}
	map[i] = NULL;
	return (map);
}

char	**parse_map(char *filename, t_game *game)
{
	int		fd;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	game->map_height = count_lines(filename);
	map = read_map_lines(fd, game);
	close(fd);
	return (map);
}
