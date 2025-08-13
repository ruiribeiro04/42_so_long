/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:49:36 by ruiferna          #+#    #+#             */
/*   Updated: 2025/08/01 01:57:39 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	init_struct_vars_as_null(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->img_wall = NULL;
	game->img_empty = NULL;
	game->img_collectible = NULL;
	game->img_exit = NULL;
	game->img_player_left = NULL;
	game->img_player_right = NULL;
	game->img_player = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->exit_x = 0;
	game->exit_y = 0;
	game->collectibles = 0;
	game->collected = 0;
	game->moves = 0;
}

int	init_game(t_game *game, char *map_file)
{
	init_struct_vars_as_null(game);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->map = parse_map(map_file, game);
	if (!game->map)
		return (mlx_destroy_display(game->mlx), free(game->mlx), 0);
	if (!validate_map(game))
	{
		free_map(game->map);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (0);
	}
	game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE, "so_long");
	if (!game->win)
		return (free_map(game->map), mlx_destroy_display(game->mlx),
			free(game->mlx), 0);
	init_player_position(game);
	game->collected = 0;
	game->moves = 0;
	return (1);
}

int	load_images(t_game *game)
{
	int	img_width;
	int	img_height;

	game->img_wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm",
			&img_width, &img_height);
	game->img_empty = mlx_xpm_file_to_image(game->mlx, "textures/empty.xpm",
			&img_width, &img_height);
	game->img_collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &img_width, &img_height);
	game->img_exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm",
			&img_width, &img_height);
	game->img_player_right = mlx_xpm_file_to_image(game->mlx,
			"textures/player_right.xpm", &img_width, &img_height);
	game->img_player_left = mlx_xpm_file_to_image(game->mlx,
			"textures/player_left.xpm", &img_width, &img_height);
	game->img_player = game->img_player_right;
	if (!game->img_wall || !game->img_empty || !game->img_collectible
		|| !game->img_exit || !game->img_player_right || !game->img_player_left)
		return (0);
	return (1);
}

void	init_player_position(t_game *game)
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
				game->player_x = j;
				game->player_y = i;
			}
			else if (game->map[i][j] == EXIT)
			{
				game->exit_x = j;
				game->exit_y = i;
			}
			j++;
		}
		i++;
	}
}
