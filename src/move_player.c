/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:17:12 by ruiferna          #+#    #+#             */
/*   Updated: 2025/06/13 07:38:49 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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
	move_player(game, game->player_x - 1, game->player_y);
}

void	move_right(t_game *game)
{
	move_player(game, game->player_x + 1, game->player_y);
}
