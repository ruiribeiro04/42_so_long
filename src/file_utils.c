/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 03:01:10 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/22 12:20:19 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	count_valid_lines(char *filename)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!is_empty_line(line))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int	is_valid_extension(const char *filename)
{
	const char	*basename;
	const char	*dot;
	size_t		len;

	basename = ft_strrchr(filename, '/');
	if (!basename)
		basename = filename;
	else
		basename++;
	dot = ft_strrchr(basename, '.');
	if (!dot || dot == basename)
		return (0);
	len = ft_strlen(dot);
	return (len == 4 && ft_strncmp(dot, ".ber", 4) == 0);
}
