/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:32:46 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/27 21:31:19 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft.h"
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_ttf.h"
# include "errorout.h"
# include <stdbool.h>
# include <math.h>
// # include <CL/cl.h>

# define WIN_WIDTH 600
# define WIN_HEIGHT 600
# define NAME_WIN "RTV by Bdrinkin"


typedef enum		s_e_light_type
{
	e_ambient,
	e_point,
	e_sun
}					t_e_light_type;

typedef enum		s_e_shape
{
	e_sphere,
	e_conus,
	e_cilindr,
	e_plane
}					t_e_shape;

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
}					t_sdl;;

typedef struct		s_shape
{
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

typedef struct		s_disk
{
	double			t1;
	double			t2;
}					t_disk;


typedef struct		s_cam
{
	t_vec3			opoint;
	struct s_vec3	**dir;
}					t_cam;

// typedef struct		s_cl
// {
// 	cl_platform_id	platform_id;
// 	cl_uint			num_platform;
// 	cl_device_id 	devices_id;
// 	cl_uint			num_devices;
// 	cl_context		context;
// 	cl_command_queue	command_queue;
// }					t_cl;

typedef struct		s_light
{
	t_vec3			dir;
	double			intens;
	uint8_t			type;
	t_color			color;
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
	int				x;
	int				y;
}					t_rt;

typedef struct		s_sub_find_intensity
{
	t_vec3		intersect;
	t_light		*is_light;
	t_vec3		norm;
	int			max_light;
}					t_sub_find_intensity;

int					main(void);
void				event_list(t_rt *rt);
void				mouse_events(t_rt *rt);
int					which_button(bool *mouse);
// t_color				trace_ray(t_cam ray, t_rt *rt, t_shape *shape, t_light *in_light);
t_color				trace_ray(t_vec3 dir, t_vec3 opoint, t_rt *rt, t_shape *shape, t_light *is_light);



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

t_disk				sphere_intersect(t_shape shape, t_vec3 cam,
						t_vec3 direction);
// t_disk				plane_intersect(t_cam ray, t_vec3 center, t_vec3 norm);

t_disk				plane_intersect(t_vec3 opoint, t_vec3 dir, t_vec3 center, t_vec3 norm);
t_disk				cylinder_intersect(t_shape shape, t_vec3 cam, t_vec3 direction);


double				find_intensity(t_vec3 intersect, t_light *is_light, t_vec3 norm, int max_light);
double				light(t_vec3 intersect, t_vec3 l_point,
						t_vec3 norm, double intensity);
t_vec3				equation_variable(t_vec3 direction, t_vec3 cam_center);


void				coleidoscope(t_rt *rt, t_point pixel, t_vec3 a);
void				pixel_shader(t_rt *rt, t_point pixel, t_vec3 dir);
void				shading(t_rt *rt);

#endif