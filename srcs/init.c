/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:23:58 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/22 13:09:57 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	*convert_to_uint32(Uint32 *dest, t_texture *image)
{
	int		x;
	int		y;
	Uint32	*pixels;

	pixels = (Uint32*)image->pixels;
	y = -1;
	while (++y < image->h)
	{
		x = -1;
		while (++x < image->w)
		{
			dest[(y * image->w) + x] = swap_channels(pixels[
				(y * image->w) + x]);
		}
	}
	return (dest);
}

void	load_texture(char *path, t_env *env, int i)
{
	t_png		png;
	t_texture	*image;

	png = png_parser(path);
	image = create_texture(&png, i);
	if (image == NULL)
		error_output("Failed to create texture from png\n");
	else
	{
		if (!(env->texture_buffer[i] = malloc(sizeof(Uint32) *
			(image->pitch * image->h))))
			error_output("Memory allocation failed!\n");
		convert_to_uint32(env->texture_buffer[i], image);
		free_png(png);
		free_texture(image);
	}
}

void	init_textures(t_env *env)
{
	load_texture("assets/textures/greybrick.png", env, 0);
	load_texture("assets/textures/redbrick.png", env, 1);
	load_texture("assets/textures/wood.png", env, 2);
	load_texture("assets/textures/eagle.png", env, 3);
}

int		init_sdl(t_env *env)
{
	env->window = NULL;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) < 0)
		return (-1);
	env->window = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	if (env->window == NULL)
		return (-1);
	env->image = SDL_GetWindowSurface(env->window);
	if (env->image == NULL)
		return (-1);
	init_textures(env);
	return (1);
}

void	init_values(t_values *p, t_map *m)
{
	p->x = -1;
	p->y = -1;
	get_player_position(p, m);
	p->ticks_last_frame = 0;
	p->turn_dir = 0;
	p->turn_speed = 45 * (PI / 180);
	p->walk_dir = 0;
	p->walk_speed = 100;
	p->w = 1;
	p->h = 1;
	p->minimap = 1;
	p->untextured = 0;
	p->shadows = 1;
	p->fps_locked = 1;
	p->fps = 30;
	p->rotation_angle = PI * 0.5;
	p->fov_angle = (60 * (PI / 180));
	p->frame_time_length = (1000 / p->fps);
	p->x = p->x * TILE_SIZE + (TILE_SIZE * 0.5);
	p->y = p->y * TILE_SIZE + (TILE_SIZE * 0.5);
	p->project_plane = ((WIN_WIDTH * 0.5) / tan(p->fov_angle * 0.5));
}
