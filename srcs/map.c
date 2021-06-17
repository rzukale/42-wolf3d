/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 12:42:25 by rzukale           #+#    #+#             */
/*   Updated: 2021/03/24 14:43:40 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	load_map(char *argv, t_map *m)
{
	int		fd;
	int		y;
	char	*line;

	y = 0;
	m->widest = 0;
	if ((fd = open(argv, O_RDONLY)) < 0)
		error_output("Map is not valid\n");
	while ((get_next_line(fd, &line)) > 0)
	{
		validate_and_fill(line, m, y);
		ft_strdel(&line);
		y++;
	}
	if (y == 0 || y > MAX_LENGTH)
		error_output("Map is not valid\n");
	m->length = y;
	close(fd);
}

void	validate_and_fill(char *line, t_map *m, int y)
{
	int		i;
	char	**markers;

	i = 0;
	markers = ft_strsplit(line, ' ');
	while (markers[i] != NULL)
	{
		if (validate(markers[i]) != 1)
			error_output("Map is not valid\n");
		i++;
	}
	if (i > MAX_WIDTH || i == 0)
		error_output("Map is not valid\n");
	if (m->widest < i)
	{
		m->widest = i;
	}
	fill_map(m->map, markers, y);
	cleanup(markers);
}

void	fill_map(int map[MAX_LENGTH][MAX_WIDTH], char **markers, int y)
{
	int	marker;
	int	i;

	i = 0;
	while (markers[i] != NULL)
	{
		marker = ft_atoi(markers[i]);
		if (marker >= 0 && marker <= 7)
			map[y][i] = marker;
		i++;
	}
}

int		validate(char *str)
{
	int i;

	i = ft_atoi(str);
	if (ft_strlen(str) == 1 && ft_isdigit(str[0]) == 1 && i >= 0 && i <= 7)
		return (1);
	return (-1);
}

int		get_player_position(t_values *p, t_map *m)
{
	int i;
	int j;

	i = 0;
	while (i < m->length)
	{
		j = 0;
		while (j < m->widest)
		{
			if (m->map[i][j] == 0)
				assign_player_position(p, i, j);
			else if (m->map[i][j] == 7)
			{
				p->y = i;
				p->x = j;
				clean_spawn_points(m);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (1);
}
