/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 16:31:36 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/16 16:25:21 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <SDL2/SDL.h>
# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include "parser_structs.h"
# include "png_parser.h"

# define FLOAT_MAX 3.402823e+38
# define MAX_WIDTH 100
# define MAX_LENGTH 100
# define NUM_TEXTURES 4
# define PI 3.14159265
# define TWO_PI 6.28318530
# define FPS_INTERVAL 1.0
# define TILE_SIZE 64
# define WIN_WIDTH 460
# define WIN_HEIGHT 420
# define MINIMAP_SCALE 0.3
# define RGB_BLACK 0xFF000000
# define RGB_WHITE 0xFFFFFFFF
# define RGB_RED 0xFFFF0000
# define RGB_GREEN 0xFF008000
# define RGB_GREY 0xFF808080
# define RGB_BLUE 0xFF0000FF
# define RGB_BROWN 0xFFA52A2A
# define RGB_AMAZON 0xFF577A3B

typedef	struct		s_values
{
	float			x;
	float			y;
	float			w;
	float			h;
	int				turn_dir;
	int				walk_dir;
	int				minimap;
	int				untextured;
	int				shadows;
	int				fps;
	int				fps_locked;
	Uint32			fps_last;
	Uint32			fps_frames;
	Uint32			ticks_last_frame;
	float			rotation_angle;
	float			walk_speed;
	float			turn_speed;
	float			project_plane;
	float			fov_angle;
	float			frame_time_length;

}					t_values;

typedef	struct		s_ray
{
	float			ray_angle;
	float			wall_hit_x;
	float			wall_hit_y;
	float			distance;
	int				hit_vertical;
	int				ray_is_up;
	int				ray_is_down;
	int				ray_is_left;
	int				ray_is_right;
	int				hit_wall_type;
}					t_ray;

typedef	struct		s_grid
{
	int				found_wall;
	float			wall_hit_x;
	float			wall_hit_y;
	int				wall_content;
	float			hit_distance;
}					t_grid;

typedef	struct		s_step
{
	float			x_intercept;
	float			y_intercept;
	float			x_step;
	float			y_step;
	float			x_check;
	float			y_check;
	float			touch_x;
	float			touch_y;
}					t_step;

typedef	struct		s_line
{
	float			x_increment;
	float			y_increment;
	float			current_x;
	float			current_y;
}					t_line;

typedef	struct		s_vertex
{
	int				x;
	int				y;
}					t_vertex;

typedef struct		s_project
{
	int				strip_height;
	int				wall_top_pixel;
	int				wall_bottom_pixel;
	int				distance_from_top;
	int				tex_offset_y;
	int				tex_offset_x;
	float			perp_distance;
	float			wall_height;
}					t_project;

typedef	struct		s_map
{
	int				map[MAX_WIDTH][MAX_LENGTH];
	int				widest;
	int				length;
}					t_map;

typedef struct		s_env
{
	SDL_Window		*window;
	SDL_Surface		*image;
	Uint32			**texture_buffer;
	t_values		p;
	t_ray			*rays;
	t_map			m;
	Uint32			*buffer;
}					t_env;

Uint32				swap_channels(unsigned int color);
void				*convert_to_uint32(Uint32 *dest, t_texture *image);
void				clean_spawn_points(t_map *m);
void				usage(void);
Uint32				get_texel_color(t_ray *ray, t_project p,
					Uint32 **texture_buffer);
Uint32				get_color(t_ray ray);
t_project			calc_proj(int y, float rot_angle,
					float project_plane, t_ray ray);
float				get_distance(float x1, float y1, float x2, float y2);
void				check_angle_direction(float angle, t_ray *ray);
void				normalize_angle(float *ray_angle);
void				render_untextured(t_values *pl, t_ray *rays,
					Uint32 *buffer);
void				render_textured(t_values *pl, t_ray *rays, Uint32 *buffer,
					Uint32 *texture_buffer[NUM_TEXTURES]);
Uint32				color_shading(Uint32 color, float factor, int shadows);
void				cast_ray(float ray_angle, t_ray *ray,
					t_map *m, t_values *p);
void				compare_distances(t_grid horz, t_grid vert,
					t_ray *ray, float ray_angle);
t_grid				check_vert_grid(float ray_angle, t_ray *ray,
					t_map *m, t_values *p);
t_grid				check_horz_grid(float ray_angle, t_ray *ray,
					t_map *m, t_values *p);
t_grid				wall_found(float x, float y, int content);
t_step				init_grid_vals(float ray_angle, t_values *p,
					t_ray *ray, int vert);
t_grid				init_grid(void);
void				cast_rays(t_ray *rays, t_values *p, t_map *map);
void				cleanup(char **array);
int					validate(char *str);
void				fill_map(int map[MAX_LENGTH][MAX_WIDTH],
					char **markers, int y);
void				validate_and_fill(char *line, t_map *m, int y);
void				load_map(char *argv, t_map *m);
void				allocate_memory(t_env *e);
void				free_all(t_env *env);
void				run_game(t_env *env);
void				render_map(Uint32 *buffer, t_map *map,
					t_values *p, t_ray *rays);
void				render_projection(t_values *p, t_ray *rays, Uint32 *buffer,
					Uint32 *texture_buffer[NUM_TEXTURES]);
void				render_buffer(Uint32 *buffer, t_env *env);
void				clear_buffer(Uint32 *buffer);
void				render_rays(t_ray *rays, int x, int y, Uint32 *buffer);
void				draw_line(t_vertex s, t_vertex e, Uint32 *buffer);
void				render_minimap(Uint32 *buffer, t_map *m);
void				draw_rectangle(t_vertex s, Uint32 color, Uint32 *buffer);
void				draw_pixel(int x, int y, Uint32 color, Uint32 *buffer);
void				update(t_values *p, t_map *m, t_ray *rays);
void				update_player(t_values *p, t_map *map, float delta_time);
int					check_collision(float new_x, float new_y, t_map *m);
void				process_inputs(t_values *p, int *quit, SDL_Event *e);
void				key_press(t_values *p, int *quit, SDL_KeyCode sym);
void				error_output(char *msg);
int					get_player_position(t_values *p, t_map *m);
void				init_values(t_values *p, t_map *m);
int					init_sdl(t_env *env);
void				init_textures(t_env *env);
void				load_texture(char *path, t_env *env, int i);
void				assign_player_position(t_values *p, int i, int j);
void				change_max_fps(t_values *p);
void				init_fps(t_values *p);
void				toggle_fps_throttling(t_values *p);

#endif
