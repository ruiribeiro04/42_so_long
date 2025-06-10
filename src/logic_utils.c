/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:37:53 by ruiferna          #+#    #+#             */
/*   Updated: 2025/06/10 18:18:47 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	move_player(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map_width || new_y < 0 ||
		new_y >= game->map_height)
		return ;
	if (game->map[new_y][new_x] == WALL)
		return ;
	if (game->map[new_y][new_x] == COLLECTIBLE)
	{
		game->collected++;
		game->map[new_y][new_x] = EMPTY;
	}
	if (game->map[new_y][new_x] == EXIT
		&& game->collected == game->collectibles)
	{
		ft_printf("Congratulations! You won in %d moves!\n", game->moves + 1);
		close_game(game);
	}
	else if (game->map[new_y][new_x] == EXIT)
		return ;
	game->map[game->player_y][game->player_x] = EMPTY;
	game->player_x = new_x;
	game->player_y = new_y;
	game->map[game->player_y][game->player_x] = PLAYER;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	render_map(game);
}

int	check_win_condition(t_game *game)
{
	return (game->collected == game->collectibles);
}