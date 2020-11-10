/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:32:46 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/10 17:59:24 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# ifdef __linux__
#  include "SDL2/SDL.h"
#  include "SDL2/SDL_image.h"
#  include "SDL2/SDL_ttf.h"
# elif __APPLE__
#  include "SDL.h"
#  include "SDL_image.h"
#  include "SDL_ttf.h"
# endif
# include "libft.h"
# include "errorout.h"
# include "colors.h"
# include <stdbool.h>
# include <math.h>

# define GET_SECTIONS 1
# define GET_PAPARAM 2

# define SPHERE 1
# define CYLINDER 2
# define CONE 3
# define PLANE 4
# define LIGHT 5
# define CAM 6

# define SPHERE_T "[sphere]"
# define CYLINDER_T "[cylinder]"
# define CONE_T "[cone]"
# define PLANE_T "[plane]"
# define LIGHT_T "[light]"
# define CAM_T "[cam]"

# define WIN_WIDTH 600
# define WIN_HEIGHT 600
# define M_PI_180 M_PI / 180
# define NAME_WIN "RTV by Bdrinkin & Ecelsa"

typedef enum		e_light_type
{
	e_ambient,
	e_point,
	e_sun
}					t_e_light_type;

typedef enum		e_shape
{
	e_sphere,
	e_conus,
	e_cilindr,
	e_plane
}					t_e_shape;

typedef struct		s_disk
{
	double			t1;
	double			t2;
}					t_disk;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_vec2
{
	double			x;
	double			y;
}					t_vec2;

typedef struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct		s_vec4
{
	double			a;
	double			b;
	double			c;
	double			d;
}					t_vec4;

typedef struct		s_mouse
{
	bool			is_presed;
	int				prew_x;
	int				prew_y;
	int				x;
	int				y;
}					t_mouse;

typedef struct		s_color
{
	uint8_t			red;
	uint8_t			green;
	uint8_t			blue;
}					t_color;

typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*screen;
	SDL_Event		event;
	int				win_hight;
	int				win_width;
	int				win_hight_old;
	int				win_width_old;
}					t_sdl;

typedef struct		s_shape
{
	int				fil;
	uint8_t			type;
	t_vec3			center;
	double			specular;
	t_vec3			norm;
	t_vec3			axis;
	double			rad;
	t_color			color;
	double			k;
	double			pow_k;
}					t_shape;

typedef struct		s_con_ax
{
	double			angle;
	t_vec3			axis;
}					t_con_ax;

typedef struct		s_cil_ax
{
	double			rad;
	t_vec3			axis;
}					t_cil_ax;

typedef struct		s_cam
{
	t_vec3			opoint;
	struct s_vec3	dir[WIN_HEIGHT][WIN_WIDTH];
}					t_cam;

typedef struct		s_light
{
	int				fil;
	t_vec3			dir;
	double			intens;
	uint8_t			type;
	t_color			color;
	int				max_light;
	bool			on;
}					t_light;

typedef struct		s_rt
{
	t_sdl			sdl;
	t_shape			*shapes;
	t_mouse			mouse;
	t_light			*light;
	t_cam			cam;
	int				max_shape;
	int				max_light;
	t_point			limit;
	bool			quit;
	t_vec3			rot;
	int				x;
	int				y;
}					t_rt;

typedef struct		s_4vec3
{
	t_vec3			a;
	t_vec3			r;
	t_vec3			b;
	t_vec3			c;
}					t_4vec3;

typedef struct		s_d_norm
{
	t_vec3			dir;
	t_vec3			norm;
}					t_d_norm;

typedef struct		s_shine
{
	t_vec3			lvec;
	t_vec3			norm;
	t_color			color;
	t_light			light;
	t_vec3			dir;
	double			shine;
}					t_shine;

typedef struct		s_sub_parser
{
	t_vec3		opoint;
	t_vec3		dir;
	t_vec3		center;
	t_vec3		axis;
	t_vec3		norm;
	t_color		color;
	t_vec3		rot;
	double		rad;
	double		angle;
	double		specular;
	int			type;
	double		intens;
	bool		on;
	int			fr;
}					t_sub_parser;

typedef struct		s_intersect
{
	t_vec3			intersect;
	int				iter;
	double			point;
	t_color			color;
	double			shine;
}					t_intersect;

void				cache_cam(t_rt *rt);

void				event_list(t_rt *rt);
void				mouse_events(t_rt *rt);
int					which_button(bool *mouse);
t_color				trace_ray(t_vec3 dir, t_vec3 opoint, t_rt *rt,
						t_shape *shape, t_light *is_light);

int					put_error_sys(char *error);
bool				put_error_sdl(char *error, const char *error_sdl);
bool				init_lib_sdl(t_rt *rt);

double				mod3(t_vec3 vec);
double				multiplication(t_vec3 v1, t_vec3 v2);
double				acos_vec3(t_vec3 v1, t_vec3 v2);
double				dot3(t_vec3 v1, t_vec3 v2);
t_vec3				subtraction3(t_vec3 v1, t_vec3 v2);
t_vec3				addition3(t_vec3 v1, t_vec3 v2);
t_vec3				normalize(t_vec3 vector);
double				clamp(double x, double min, double max);
t_vec3				cross(t_vec3 a, t_vec3 b);
void				clear_surface(SDL_Surface *surface, Uint32 color);
t_vec3				cross_scalar(t_vec3 vect, double scalar);

double				sphere_intersect(t_shape shape, t_vec3 cam,
						t_vec3 direction);
double				conus_intersect(t_shape shape, t_vec3 opoint,
						t_vec3 direction);
double				plane_intersect(t_vec3 opoint, t_vec3 dir,
						t_vec3 center, t_vec3 norm);
double				cylinder_intersect(t_shape shape, t_vec3 cam,
						t_vec3 direction);
t_vec3				parallel_transfer3(t_vec3 a, t_vec3 b);

double				find_intensity(t_vec3 intersect, t_light *is_light,
						t_vec3 norm, int max_light);
double				light(t_vec3 intersect, t_vec3 l_point,
						t_vec3 norm, double intensity);
t_vec3				equation_variable(t_vec3 direction, t_vec3 cam_center);
void				keyboard_events(t_rt *rt, SDL_Keycode sym);

void				coleidoscope(t_rt *rt, t_point pixel, t_vec3 a);
t_color				pixel_shader(t_vec3 dir, t_vec3 opoint, t_rt *rt);
void				shading(t_rt *rt);
double				ft_min_d(double v1, double v2);
void				recache_cam(t_rt *rt);
void				rt_free(t_rt *rt);
void				color_fill(t_color *dst, t_color src);
t_color				mix_color(t_color color, double intensity);
t_vec3				surface_norm(t_intersect param, t_shape shape,
						t_vec3 opoint, t_vec3 dir);
t_color				lighting_calculation(t_intersect param, t_light *light,
						t_d_norm dn, t_rt *rt);

void				init_cam(t_rt *rt);
double				equal_min(double min[2], int i, t_intersect *param);
bool				shadow_calc(t_light light, t_intersect itr,
						t_vec3 n_p, t_color *color);
t_intersect			ray_intersect(t_vec3 dir, t_vec3 opoint,
						t_shape *shape, int count_shape);
t_color				shine_calc(t_shine s);

int					parse_fail(char *file_name, t_rt *rt);
t_shape				create_sphere(t_sub_parser data);
t_shape				create_plane(t_sub_parser data);
t_shape				create_cone(t_sub_parser data);
t_shape				create_cilinder(t_sub_parser data);
t_light				create_light_point(t_sub_parser data, int max_light);
t_light				create_light_ambient(t_sub_parser data, int max_light);
void				create_cam(t_rt *rt, t_sub_parser data);

#endif
