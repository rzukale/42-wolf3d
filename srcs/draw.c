/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:27:28 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/23 12:53:25 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_line(t_vertex s, t_vertex e, Uint32 *buffer)
{
	t_vertex	delta;
	t_line		l;
	int			length;
	int			i;

	delta.x = (e.x - s.x);
	delta.y = (e.y - s.y);
	length = (ft_abs(delta.x) >= ft_abs(delta.y)) ?
		ft_abs(delta.x) : ft_abs(delta.y);
	l.x_increment = delta.x / (float)length;
	l.y_increment = delta.y / (float)length;
	l.current_x = s.x;
	l.current_y = s.y;
	i = -1;
	while (++i <= length)
	{
		draw_pixel(round(l.current_x), round(l.current_y), RGB_RED, buffer);
		l.current_x += l.x_increment;
		l.current_y += l.y_increment;
	}
}

void	draw_pixel(int x, int y, Uint32 color, Uint32 *buffer)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		buffer[(WIN_WIDTH * y) + x] = color;
}

void	draw_rectangle(t_vertex s, Uint32 color, Uint32 *buffer)
{
	int		x;
	int		y;
	int		w;
	int		h;

	w = TILE_SIZE * MINIMAP_SCALE;
	h = TILE_SIZE * MINIMAP_SCALE;
	x = s.x;
	while (x <= (s.x + w))
	{
		y = s.y;
		while (y <= (s.y + h))
		{
			draw_pixel(x, y, color, buffer);
			y++;
		}
		x++;
	}
}
