/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:37:53 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/22 12:20:19 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	update_player_position(t_game *game, int new_x, int new_y)
{
	if (game->map[game->player_y][game->player_x] != EXIT)
		game->map[game->player_y][game->player_x] = EMPTY;
	game->player_x = new_x;
	game->player_y = new_y;
	if (game->map[game->player_y][game->player_x] != EXIT)
		game->map[game->player_y][game->player_x] = PLAYER;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

void	move_player(t_game *game, int new_x, int new_y)
{
	if (!is_valid_move(game, new_x, new_y))
		return ;
	handle_collectible(game, new_x, new_y);
	handle_exit(game, new_x, new_y);
	update_player_position(game, new_x, new_y);
	render_map(game);
}

int	is_valid_move(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map_width || new_y < 0
		|| new_y >= game->map_height)
		return (0);
	if (game->map[new_y][new_x] == WALL)
		return (0);
	return (1);
}

void	handle_collectible(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == COLLECTIBLE)
	{
		game->collected++;
		game->map[new_y][new_x] = EMPTY;
	}
}

void	handle_exit(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == EXIT
		&& game->collected == game->collectibles)
	{
		ft_printf("Congratulations! You won in %d moves!\n", game->moves + 1);
		close_game(game);
	}
}
