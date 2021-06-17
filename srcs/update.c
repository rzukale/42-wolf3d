/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:07:20 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/22 16:27:23 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	update_player(t_values *p, t_map *map, float delta_time)
{
	float move_step;
	float new_player_x;
	float new_player_y;

	p->rotation_angle += p->turn_dir * p->turn_speed * delta_time;
	move_step = p->walk_dir * p->walk_speed * delta_time;
	new_player_x = p->x + cos(p->rotation_angle) * move_step;
	new_player_y = p->y + sin(p->rotation_angle) * move_step;
	if (!check_collision(new_player_x, new_player_y, map))
	{
		p->x = new_player_x;
		p->y = new_player_y;
	}
}

void	update(t_values *p, t_map *m, t_ray *rays)
{
	int		time_out;
	float	delta_time;

	if (p->fps_locked)
	{
		time_out = p->frame_time_length - (SDL_GetTicks() -
			p->ticks_last_frame);
		if (time_out > 0)
			SDL_Delay(time_out);
	}
	delta_time = (SDL_GetTicks() - p->ticks_last_frame) / 1000.0f;
	p->ticks_last_frame = SDL_GetTicks();
	update_player(p, m, delta_time);
	cast_rays(rays, p, m);
}

void	render_buffer(Uint32 *buffer, t_env *env)
{
	SDL_LockSurface(env->image);
	ft_memcpy(env->image->pixels, buffer, env->image->pitch * env->image->h);
	SDL_UnlockSurface(env->image);
	SDL_UpdateWindowSurface(env->window);
}

void	render_map(Uint32 *buffer, t_map *map, t_values *p, t_ray *rays)
{
	render_minimap(buffer, map);
	render_rays(rays, p->x, p->y, buffer);
}

void	run_game(t_env *env)
{
	SDL_Event	e;
	int			quit;
	char		*fps;

	quit = -1;
	init_fps(&env->p);
	while (quit == -1)
	{
		process_inputs(&env->p, &quit, &e);
		update(&env->p, &env->m, env->rays);
		clear_buffer(env->buffer);
		render_projection(&env->p, env->rays, env->buffer, env->texture_buffer);
		if (env->p.minimap)
			render_map(env->buffer, &env->m, &env->p, env->rays);
		render_buffer(env->buffer, env);
		env->p.fps_frames++;
		if (env->p.fps_last < SDL_GetTicks() - FPS_INTERVAL * 1000)
		{
			env->p.fps_last = SDL_GetTicks();
			fps = ft_itoa(env->p.fps_frames);
			env->p.fps_frames = 0;
			SDL_SetWindowTitle(env->window, fps);
			free(fps);
		}
	}
}
