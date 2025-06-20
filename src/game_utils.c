/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:51:24 by ruiferna          #+#    #+#             */
/*   Updated: 2025/06/13 07:51:45 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	close_game(t_game *game)
{
	clean_game(game);
	exit(0);
}

int	count_lines(char *filename)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

int	is_directory(const char *path)
{
	int		fd;
	char	buf;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	if (read(fd, &buf, 1) < 0)
	{
		if (errno == EISDIR)
		{
			close(fd);
			return (1);
		}
	}
	close(fd);
	return (0);
}
