/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:34:48 by rzukale           #+#    #+#             */
/*   Updated: 2021/03/26 17:19:58 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	cleanup(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_strdel(&array[i]);
		i++;
	}
	free(array);
}

void	free_all(t_env *env)
{
	int i;

	free(env->rays);
	i = -1;
	while (++i < NUM_TEXTURES)
		free(env->texture_buffer[i]);
	free(env->texture_buffer);
	free(env->buffer);
	SDL_DestroyWindow(env->window);
}

void	allocate_memory(t_env *e)
{
	if (!(e->texture_buffer = (Uint32**)malloc(sizeof(Uint32*) * NUM_TEXTURES)))
		error_output("Memory allocation failed!\n");
	if (!(e->rays = (t_ray*)malloc(sizeof(t_ray) * WIN_WIDTH)))
		error_output("Memory allocation failed!\n");
	if (!(e->buffer = (Uint32*)malloc(sizeof(Uint32) *
		(Uint32)WIN_WIDTH * (Uint32)WIN_HEIGHT)))
		error_output("Memory allocation failed!\n");
}

void	clear_buffer(Uint32 *buffer)
{
	int i;

	i = 0;
	while (i < (WIN_WIDTH * WIN_HEIGHT))
	{
		buffer[i] = RGB_BLACK;
		i++;
	}
}
