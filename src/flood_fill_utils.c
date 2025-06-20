/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:26:50 by ruiferna          #+#    #+#             */
/*   Updated: 2025/06/20 12:29:56 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	flood_fill_collectibles(char **map, int x, int y, t_game *game)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return ;
	if (map[y][x] == WALL || map[y][x] == 'V' || map[y][x] == EXIT)
		return ;
	map[y][x] = 'V';
	flood_fill_collectibles(map, x + 1, y, game);
	flood_fill_collectibles(map, x - 1, y, game);
	flood_fill_collectibles(map, x, y + 1, game);
	flood_fill_collectibles(map, x, y - 1, game);
}

void	flood_fill_exit(char **map, int x, int y, t_game *game)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return ;
	if (map[y][x] == WALL || map[y][x] == 'V' || map[y][x] == COLLECTIBLE)
		return ;
	map[y][x] = 'V';
	flood_fill_exit(map, x + 1, y, game);
	flood_fill_exit(map, x - 1, y, game);
	flood_fill_exit(map, x, y + 1, game);
	flood_fill_exit(map, x, y - 1, game);
}

int	validate_collectibles_access(char **map_copy, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == COLLECTIBLE && map_copy[i][j] != 'V')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_exit_access(char **map_copy, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == EXIT && map_copy[i][j] != 'V')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
