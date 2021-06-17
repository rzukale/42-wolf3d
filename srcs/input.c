/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:27:54 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/16 16:25:03 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	key_press(t_values *p, int *quit, SDL_KeyCode sym)
{
	if (sym == SDLK_ESCAPE)
		*quit = 1;
	else if (sym == SDLK_UP)
		p->walk_dir = 1;
	else if (sym == SDLK_DOWN)
		p->walk_dir = -1;
	else if (sym == SDLK_LEFT)
		p->turn_dir = -1;
	else if (sym == SDLK_RIGHT)
		p->turn_dir = 1;
	else if (sym == SDLK_m)
		p->minimap = (p->minimap == 1) ? 0 : 1;
	else if (sym == SDLK_t)
		p->untextured = (p->untextured == 1) ? 0 : 1;
	else if (sym == SDLK_u)
		p->shadows = (p->shadows == 1) ? 0 : 1;
	else if (sym == SDLK_f)
		change_max_fps(p);
	else if (sym == SDLK_l)
		toggle_fps_throttling(p);
}

void	process_inputs(t_values *p, int *quit, SDL_Event *e)
{
	while (SDL_PollEvent(e) != 0)
	{
		if (e->type == SDL_QUIT)
			*quit = 1;
		if (e->type == SDL_KEYDOWN)
		{
			key_press(p, quit, e->key.keysym.sym);
		}
		else if (e->type == SDL_KEYUP)
		{
			if (e->key.keysym.sym == SDLK_UP)
				p->walk_dir = 0;
			else if (e->key.keysym.sym == SDLK_DOWN)
				p->walk_dir = 0;
			else if (e->key.keysym.sym == SDLK_LEFT)
				p->turn_dir = 0;
			else if (e->key.keysym.sym == SDLK_RIGHT)
				p->turn_dir = 0;
		}
	}
}
