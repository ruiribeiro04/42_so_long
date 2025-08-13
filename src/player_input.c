/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:51:24 by ruiferna          #+#    #+#             */
/*   Updated: 2025/08/01 01:57:39 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	keypress_handler(int key, t_game *game)
{
	if (key == ESC_KEY)
		close_game(game);
	else if (key == W_KEY || key == UP_KEY)
		move_up(game);
	else if (key == A_KEY || key == LEFT_KEY)
		move_left(game);
	else if (key == S_KEY || key == DOWN_KEY)
		move_down(game);
	else if (key == D_KEY || key == RIGHT_KEY)
		move_right(game);
	return (0);
}

void	move_up(t_game *game)
{
	move_player(game, game->player_x, game->player_y - 1);
}

void	move_down(t_game *game)
{
	move_player(game, game->player_x, game->player_y + 1);
}

void	move_left(t_game *game)
{
	game->img_player = game->img_player_left;
	move_player(game, game->player_x - 1, game->player_y);
}

void	move_right(t_game *game)
{
	game->img_player = game->img_player_right;
	move_player(game, game->player_x + 1, game->player_y);
}
