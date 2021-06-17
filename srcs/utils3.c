/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 20:27:59 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/26 10:29:17 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_fps(t_values *p)
{
	p->fps_last = SDL_GetTicks();
	p->fps_frames = 0;
}

void	change_max_fps(t_values *p)
{
	p->fps = (p->fps == 30) ? 60 : 30;
	p->frame_time_length = (1000 / p->fps);
	ft_putstr("FPS cap switched to ");
	ft_putnbr(p->fps);
	ft_putchar('\n');
}

void	toggle_fps_throttling(t_values *p)
{
	p->fps_locked = (p->fps_locked == 1) ? 0 : 1;
	if (p->fps_locked)
		ft_putstr("FPS throttling ON\n");
	else
		ft_putstr("FPS throttling OFF\n");
}

Uint32	swap_channels(unsigned int color)
{
	Uint8 red;
	Uint8 green;
	Uint8 blue;
	Uint8 alpha;

	red = (color >> 24);
	green = (color >> 16);
	blue = (color >> 8);
	alpha = (color);
	return ((alpha << 24) | (red << 16) | (green << 8) | (blue));
}
