/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:12:36 by rzukale           #+#    #+#             */
/*   Updated: 2021/03/26 17:15:45 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	cast_rays(t_ray *rays, t_values *p, t_map *map)
{
	int		x;
	float	ray_angle;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ray_angle = p->rotation_angle +
			atan((x - WIN_WIDTH * 0.5) / p->project_plane);
		cast_ray(ray_angle, &rays[x], map, p);
		x++;
	}
}

t_grid	check_horz_grid(float ray_angle, t_ray *ray, t_map *m, t_values *p)
{
	t_grid		horz;
	t_step		v;

	horz = init_grid();
	v = init_grid_vals(ray_angle, p, ray, 0);
	v.touch_x = v.x_intercept;
	v.touch_y = v.y_intercept;
	while (v.touch_x >= 0 && v.touch_x <= (m->widest * TILE_SIZE) &&
		v.touch_y >= 0 && v.touch_y <= (m->length * TILE_SIZE))
	{
		v.x_check = v.touch_x;
		v.y_check = v.touch_y + (ray->ray_is_up ? -1 : 0);
		if (check_collision(v.x_check, v.y_check, m) == 1)
		{
			horz = wall_found(v.touch_x, v.touch_y, m->map[(int)
			floor(v.y_check / TILE_SIZE)][(int)floor(v.x_check / TILE_SIZE)]);
			break ;
		}
		else
		{
			v.touch_x += v.x_step;
			v.touch_y += v.y_step;
		}
	}
	return (horz);
}

t_grid	check_vert_grid(float ray_angle, t_ray *ray, t_map *m, t_values *p)
{
	t_grid		vert;
	t_step		v;

	vert = init_grid();
	v = init_grid_vals(ray_angle, p, ray, 1);
	v.touch_x = v.x_intercept;
	v.touch_y = v.y_intercept;
	while (v.touch_x >= 0 && v.touch_x <= (m->widest * TILE_SIZE) &&
		v.touch_y >= 0 && v.touch_y <= (m->length * TILE_SIZE))
	{
		v.x_check = v.touch_x + (ray->ray_is_left ? -1 : 0);
		v.y_check = v.touch_y;
		if (check_collision(v.x_check, v.y_check, m))
		{
			vert = wall_found(v.touch_x, v.touch_y, m->map[(int)
			floor(v.y_check / TILE_SIZE)][(int)floor(v.x_check / TILE_SIZE)]);
			break ;
		}
		else
		{
			v.touch_x += v.x_step;
			v.touch_y += v.y_step;
		}
	}
	return (vert);
}

void	compare_distances(t_grid horz, t_grid vert, t_ray *ray, float ray_angle)
{
	if (vert.hit_distance < horz.hit_distance)
	{
		ray->distance = vert.hit_distance;
		ray->wall_hit_x = vert.wall_hit_x;
		ray->wall_hit_y = vert.wall_hit_y;
		ray->hit_wall_type = vert.wall_content;
		ray->hit_vertical = 1;
	}
	else
	{
		ray->distance = horz.hit_distance;
		ray->wall_hit_x = horz.wall_hit_x;
		ray->wall_hit_y = horz.wall_hit_y;
		ray->hit_wall_type = horz.wall_content;
		ray->hit_vertical = 0;
	}
	ray->ray_angle = ray_angle;
}

void	cast_ray(float ray_angle, t_ray *ray, t_map *m, t_values *p)
{
	t_grid	horz;
	t_grid	vert;

	normalize_angle(&ray_angle);
	check_angle_direction(ray_angle, ray);
	horz = check_horz_grid(ray_angle, ray, m, p);
	vert = check_vert_grid(ray_angle, ray, m, p);
	horz.hit_distance = horz.found_wall
		? get_distance(p->x, p->y, horz.wall_hit_x, horz.wall_hit_y) :
		FLOAT_MAX;
	vert.hit_distance = vert.found_wall
		? get_distance(p->x, p->y, vert.wall_hit_x, vert.wall_hit_y) :
		FLOAT_MAX;
	compare_distances(horz, vert, ray, ray_angle);
}
