/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:11:08 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/22 12:20:19 by ruiferna         ###   ########.fr       */
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

static void	*get_tile_image(t_game *game, char tile)
{
	if (tile == WALL)
		return (game->img_wall);
	else if (tile == COLLECTIBLE)
		return (game->img_collectible);
	else if (tile == EXIT)
		return (game->img_exit);
	else if (tile == PLAYER)
		return (game->img_player);
	else
		return (game->img_empty);
}

void	render_tile(t_game *game, int x, int y, char tile)
{
	void	*img;

	if (x == game->player_x && y == game->player_y)
		img = game->img_player;
	else if (x == game->exit_x && y == game->exit_y)
		img = game->img_exit;
	else
		img = get_tile_image(game, tile);
	mlx_put_image_to_window(game->mlx, game->win, img, x * TILE_SIZE, y
		* TILE_SIZE);
}
