/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:11:08 by ruiferna          #+#    #+#             */
/*   Updated: 2025/06/13 07:38:44 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			render_tile(game, x, y, game->map[y][x]);
			x++;
		}
		y++;
	}
}

void	render_tile(t_game *game, int x, int y, char tile)
{
	void	*img;

	if (tile == WALL)
		img = game->img_wall;
	else if (tile == COLLECTIBLE)
		img = game->img_collectible;
	else if (tile == EXIT)
		img = game->img_exit;
	else if (tile == PLAYER)
		img = game->img_player;
	else
		img = game->img_empty;
	mlx_put_image_to_window(game->mlx, game->win, img,
		x * TILE_SIZE, y * TILE_SIZE);
}

void	update_display(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	render_map(game);
}
