/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:14:42 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/22 14:02:25 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		normalize_angle(float *ray_angle)
{
	*ray_angle = remainder(*ray_angle, TWO_PI);
	if (*ray_angle < 0)
		*ray_angle = TWO_PI + *ray_angle;
}

void		check_angle_direction(float angle, t_ray *ray)
{
	if (angle > 0 && angle < PI)
	{
		ray->ray_is_down = 1;
		ray->ray_is_up = 0;
	}
	else
	{
		ray->ray_is_down = 0;
		ray->ray_is_up = 1;
	}
	if (angle < (0.5 * PI) || angle > (1.5 * PI))
	{
		ray->ray_is_left = 0;
		ray->ray_is_right = 1;
	}
	else
	{
		ray->ray_is_left = 1;
		ray->ray_is_right = 0;
	}
}

float		get_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int			check_collision(float new_x, float new_y, t_map *m)
{
	int map_index_x;
	int map_index_y;

	if (new_x < 0 || new_x >= (m->widest * TILE_SIZE) ||
		new_y < 0 || new_y >= m->length * TILE_SIZE)
		return (1);
	map_index_x = (int)floor(new_x / TILE_SIZE);
	map_index_y = (int)floor(new_y / TILE_SIZE);
	if (m->map[map_index_y][map_index_x] != 0)
		return (1);
	return (0);
}

t_project	calc_proj(int y, float rot_angle, float project_plane, t_ray ray)
{
	t_project p;

	p.perp_distance = ray.distance * cos(ray.ray_angle - rot_angle);
	p.wall_height = (TILE_SIZE / p.perp_distance) * project_plane;
	p.strip_height = (int)p.wall_height;
	p.wall_top_pixel = (WIN_HEIGHT / 2) - (p.strip_height / 2);
	p.wall_top_pixel = p.wall_top_pixel < 0 ? 0 : p.wall_top_pixel;
	p.wall_bottom_pixel = (WIN_HEIGHT / 2) + (p.strip_height / 2);
	p.wall_bottom_pixel = p.wall_bottom_pixel > WIN_HEIGHT ? WIN_HEIGHT :
		p.wall_bottom_pixel;
	p.distance_from_top = y + (p.strip_height * 0.5) - (WIN_HEIGHT * 0.5);
	p.tex_offset_y = p.distance_from_top *
		((float)TILE_SIZE / p.strip_height);
	if (ray.hit_vertical)
		p.tex_offset_x = (int)ray.wall_hit_y % TILE_SIZE;
	else
		p.tex_offset_x = (int)ray.wall_hit_x % TILE_SIZE;
	return (p);
}
