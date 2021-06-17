/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:10:51 by rzukale           #+#    #+#             */
/*   Updated: 2021/01/18 17:20:14 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	assign_player_position(t_values *p, int i, int j)
{
	if (p->x == -1 && p->y == -1)
	{
		p->x = j;
		p->y = i;
	}
	else if ((j + i) < (p->x + p->y))
	{
		p->x = j;
		p->y = i;
	}
}

t_grid	init_grid(void)
{
	t_grid g;

	g.found_wall = 0;
	g.wall_hit_x = 0;
	g.wall_hit_y = 0;
	g.wall_content = 0;
	return (g);
}

t_step	init_grid_vals(float ray_angle, t_values *p, t_ray *ray, int vert)
{
	t_step v;

	if (vert)
	{
		v.x_intercept = floor(p->x / TILE_SIZE) * TILE_SIZE;
		v.x_intercept += ray->ray_is_right ? TILE_SIZE : 0;
		v.y_intercept = p->y + (v.x_intercept - p->x) * tan(ray_angle);
		v.x_step = TILE_SIZE;
		v.x_step *= ray->ray_is_left ? -1 : 1;
		v.y_step = TILE_SIZE * tan(ray_angle);
		v.y_step *= (ray->ray_is_up && v.y_step > 0) ? -1 : 1;
		v.y_step *= (ray->ray_is_down && v.y_step < 0) ? -1 : 1;
	}
	else
	{
		v.y_intercept = floor(p->y / TILE_SIZE) * TILE_SIZE;
		v.y_intercept += ray->ray_is_down ? TILE_SIZE : 0;
		v.x_intercept = p->x + (v.y_intercept - p->y) / tan(ray_angle);
		v.y_step = TILE_SIZE;
		v.y_step *= ray->ray_is_up ? -1 : 1;
		v.x_step = TILE_SIZE / tan(ray_angle);
		v.x_step *= (ray->ray_is_left && v.x_step > 0) ? -1 : 1;
		v.x_step *= (ray->ray_is_right && v.x_step < 0) ? -1 : 1;
	}
	return (v);
}

t_grid	wall_found(float x, float y, int content)
{
	t_grid v;

	v.wall_hit_x = x;
	v.wall_hit_y = y;
	v.wall_content = content;
	v.found_wall = 1;
	return (v);
}

void	clean_spawn_points(t_map *m)
{
	int i;
	int j;

	i = -1;
	while (++i < m->length)
	{
		j = -1;
		while (++j < m->widest)
		{
			if (m->map[i][j] == 7)
				m->map[i][j] = 0;
		}
	}
}
