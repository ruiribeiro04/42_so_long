/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:57:01 by ruiferna          #+#    #+#             */
/*   Updated: 2025/06/10 20:06:20 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_path_validity(t_game *game)
{
	char	**map_copy;
	int		player_x;
	int		player_y;
	int		result;

	map_copy = create_map_copy(game);
	if (!map_copy)
		return (0);
	find_player_position(game, &player_x, &player_y);
	flood_fill(map_copy, player_x, player_y, game);
	result = validate_accessibility(map_copy, game);
	free_map(map_copy);
	return (result);
}

char	**create_map_copy(t_game *game)
{
	char	**copy;
	int		i;
	int		j;

	copy = malloc(sizeof(char *) * (game->map_height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < game->map_height)
	{
		copy[i] = malloc(sizeof(char) * (game->map_width + 1));
		if (!copy[i])
			return (free_map_partial(copy, i), NULL);
		j = 0;
		while (j < game->map_width)
		{
			copy[i][j] = game->map[i][j];
			j++;
		}
		copy[i][j] = '\0';
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	find_player_position(t_game *game, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == PLAYER)
			{
				*x = j;
				*y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	flood_fill(char **map, int x, int y, t_game *game)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return ;
	if (map[y][x] == WALL || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
}

int	validate_accessibility(char **map_copy, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if ((game->map[i][j] == COLLECTIBLE || game->map[i][j] == EXIT) &&
				map_copy[i][j] != 'V')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}