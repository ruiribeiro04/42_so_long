/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:57:01 by ruiferna          #+#    #+#             */
/*   Updated: 2025/06/20 12:28:12 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_path_validity(t_game *game)
{
	if (!check_collectibles_reachable(game))
		return (0);
	if (!check_exit_reachable(game))
		return (0);
	return (1);
}

int	check_collectibles_reachable(t_game *game)
{
	char	**map_copy;
	int		player_x;
	int		player_y;
	int		result;

	map_copy = create_map_copy(game);
	if (!map_copy)
		return (0);
	find_player_position(game, &player_x, &player_y);
	flood_fill_collectibles(map_copy, player_x, player_y, game);
	result = validate_collectibles_access(map_copy, game);
	free_map(map_copy);
	return (result);
}

int	check_exit_reachable(t_game *game)
{
	char	**map_copy;
	int		player_x;
	int		player_y;
	int		result;

	map_copy = create_map_copy(game);
	if (!map_copy)
		return (0);
	find_player_position(game, &player_x, &player_y);
	flood_fill_exit(map_copy, player_x, player_y, game);
	result = validate_exit_access(map_copy, game);
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
