/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:51:24 by ruiferna          #+#    #+#             */
/*   Updated: 2025/06/13 07:39:05 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	keypress_handler(int key, t_game *game)
{
	if (key == ESC_KEY)
		close_game(game);
	else if (key == W_KEY)
		move_up(game);
	else if (key == A_KEY)
		move_left(game);
	else if (key == S_KEY)
		move_down(game);
	else if (key == D_KEY)
		move_right(game);
	return (0);
}
