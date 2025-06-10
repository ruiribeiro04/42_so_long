/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:56:12 by ruiferna          #+#    #+#             */
/*   Updated: 2025/06/10 18:21:10 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/minilibx-linux/mlx.h"
# include "../libs/libft/42_libft/libft.h"
# include "../libs/libft/42_ft_printf/ft_printf.h"
# include "../libs/libft/42_get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_SIZE 64
# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100

# define WALL '1'
# define EMPTY '0'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			map_width;
	int			map_height;
	int			player_x;
	int			player_y;
	int			collectibles;
	int			collected;
	int			moves;
	void		*img_wall;
	void		*img_empty;
	void		*img_collectible;
	void		*img_exit;
	void		*img_player;
}	t_game;

// error_handler.c
void	error_exit(char *message);
void	free_map(char **map);
void	free_map_partial(char **map, int allocated_rows);
void	clean_game(t_game *game);

// game_utils.c
int		close_game(t_game *game);
int		count_lines(char *filename);

// initialize_game.c
int		init_game(t_game *game, char *map_file);
int		load_images(t_game *game);
void	init_player_position(t_game *game);

// keyhandler.c
int		keypress_handler(int key, t_game *game);

// logic_utils.c
void	move_player(t_game *game, int new_x, int new_y);
int		check_win_condition(t_game *game);

// map_validator.c
int		check_path_validity(t_game *game);
char	**create_map_copy(t_game *game);
void	find_player_position(t_game *game, int *x, int *y);
void	flood_fill(char **map, int x, int y, t_game *game);
int		validate_accessibility(char **map_copy, t_game *game);

// map_validator_utils.c
int		validate_map(t_game *game);
int		check_map_walls(t_game *game);
int		check_map_elements(t_game *game);
char	**parse_map(char *filename, t_game *game);

// move_player.c
void	move_up(t_game *game);
void	move_down(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);

// rendering.c
void	render_map(t_game *game);
void	render_tile(t_game *game, int x, int y, char tile);
void	update_display(t_game *game);

#endif