/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:08:26 by rzukale           #+#    #+#             */
/*   Updated: 2021/03/26 17:13:06 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	render_textured(t_values *pl, t_ray *rays, Uint32 *buffer,
		Uint32 *texture_buffer[NUM_TEXTURES])
{
	int			x;
	int			y;
	t_project	p;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
		{
			p = calc_proj(y, pl->rotation_angle,
				pl->project_plane, rays[x]);
			if (y < p.wall_top_pixel)
				draw_pixel(x, y, color_shading(RGB_BROWN, (150 * 1 /
				get_distance(x, 0, x, y)), pl->shadows), buffer);
			else if (y >= p.wall_top_pixel && y <= p.wall_bottom_pixel)
				draw_pixel(x, y, color_shading(
					get_texel_color(&rays[x], p, texture_buffer),
					(200 * 1 / p.perp_distance), pl->shadows), buffer);
			else
				draw_pixel(x, y, color_shading(RGB_AMAZON, (200 * 1 /
				get_distance(x, WIN_HEIGHT, x, y)), pl->shadows), buffer);
		}
	}
}

void	render_untextured(t_values *pl, t_ray *rays, Uint32 *buffer)
{
	int			x;
	int			y;
	t_project	p;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			p = calc_proj(y, pl->rotation_angle,
				pl->project_plane, rays[x]);
			if (y < p.wall_top_pixel)
				draw_pixel(x, y, RGB_BROWN, buffer);
			else if (y >= p.wall_top_pixel && y <= p.wall_bottom_pixel)
				draw_pixel(x, y, get_color(rays[x]), buffer);
			else
				draw_pixel(x, y, RGB_AMAZON, buffer);
			y++;
		}
		x++;
	}
}

void	render_rays(t_ray *rays, int x, int y, Uint32 *buffer)
{
	int			i;
	t_vertex	s;
	t_vertex	e;

	i = -1;
	s.x = x * MINIMAP_SCALE;
	s.y = y * MINIMAP_SCALE;
	while (++i < WIN_WIDTH)
	{
		e.x = rays[i].wall_hit_x * MINIMAP_SCALE;
		e.y = rays[i].wall_hit_y * MINIMAP_SCALE;
		draw_line(s, e, buffer);
	}
}

void	render_minimap(Uint32 *buffer, t_map *m)
{
	int			i;
	int			j;
	t_vertex	c;
	Uint32		color;

	i = 0;
	while (i < m->length)
	{
		j = 0;
		while (j < m->widest)
		{
			color = m->map[i][j] != 0 ? RGB_WHITE : RGB_BLACK;
			c.x = j * TILE_SIZE;
			c.y = i * TILE_SIZE;
			c.x = c.x * MINIMAP_SCALE;
			c.y = c.y * MINIMAP_SCALE;
			draw_rectangle(c, color, buffer);
			j++;
		}
		i++;
	}
}

void	render_projection(t_values *p, t_ray *rays, Uint32 *buffer,
		Uint32 *texture_buffer[NUM_TEXTURES])
{
	if (p->untextured)
		render_untextured(p, rays, buffer);
	else
		render_textured(p, rays, buffer, texture_buffer);
}
