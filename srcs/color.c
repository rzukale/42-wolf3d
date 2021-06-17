/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:29:25 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/26 10:28:13 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

Uint32	get_color(t_ray ray)
{
	if (ray.hit_vertical && ray.ray_is_left)
		return (RGB_RED);
	else if (ray.hit_vertical && ray.ray_is_right)
		return (RGB_GREEN);
	else if (!ray.hit_vertical && ray.ray_is_up)
		return (RGB_GREY);
	else
		return (RGB_BLUE);
}

Uint32	get_texel_color(t_ray *ray, t_project p, Uint32 **texture_buffer)
{
	Uint32 color;

	color = 0x00000000;
	if (ray->ray_is_down && !ray->hit_vertical)
		color = texture_buffer[0][(TILE_SIZE * p.tex_offset_y) +
		p.tex_offset_x];
	else if (ray->ray_is_left && ray->hit_vertical)
		color = texture_buffer[1][(TILE_SIZE * p.tex_offset_y) +
		p.tex_offset_x];
	else if (ray->ray_is_right && ray->hit_vertical)
		color = texture_buffer[2][(TILE_SIZE * p.tex_offset_y) +
		p.tex_offset_x];
	else if (ray->ray_is_up && !ray->hit_vertical)
		color = texture_buffer[3][(TILE_SIZE * p.tex_offset_y) +
		p.tex_offset_x];
	return (color);
}

Uint32	color_shading(Uint32 color, float factor, int shadows)
{
	Uint8 alpha;
	Uint8 red;
	Uint8 green;
	Uint8 blue;

	if (shadows)
	{
		if (factor >= 1)
			factor = 1.0;
		alpha = (color >> 24);
		red = (color >> 16);
		green = (color >> 8);
		blue = (color);
		red *= factor;
		green *= factor;
		blue *= factor;
		return ((alpha << 24) | (red << 16) | (green << 8) | (blue));
	}
	return (color);
}
