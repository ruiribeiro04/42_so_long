/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:56:12 by ruiferna          #+#    #+#             */
/*   Updated: 2025/06/10 18:29:25 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// int	main(void)
// {
// 	void	*mlx;
// 	void	*win;

// 	mlx = mlx_init();
// 	if (!mlx)
// 		return (1);
// 	win = mlx_new_window(mlx, 800, 600, "so_long");
// 	if (!win)
// 		return (1);
// 	mlx_loop(mlx);
// 	return (0);
// }

int	main(int ac, char **av)
{
	t_game	game;
	// TODO: implement logic of init, error, validation, images functions
	if (ac != 2)
		error_exit("Usage: ./so_long <map_file.ber>");
	if (!init_game(&game, av[1]))
		error_exit("Error while initializing the game");
	if (!validate_map(&game))
	{
		clean_game(&game);
		error_exit("Invalid map");
	}
	if (!load_images(&game))
	{
		clean_game(&game);
		error_exit("Failed to load images");
	}
	render_map(&game);
	mlx_key_hook(game.win, keypress_handler, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
	return (0);
}