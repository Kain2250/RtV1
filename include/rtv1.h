/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kain2250 <kain2250@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:32:46 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/23 04:14:41 by kain2250         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft.h"
# include "SDL2/SDL.h"
# include "SDL2/SDL_image.h"
# include "SDL2/SDL_ttf.h"
# include "errorout.h"
# include <stdbool.h>
# include <math.h>
// # include <CL/cl.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 800
# define NAME_WIN "RTV by Bdrinkin"
# define SPHERE 0

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
	float			x;
	float			y;
}					t_vec2;

typedef struct		s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

typedef struct		s_vec4
{
	float			r;
	float			g;
	float			b;
	float			a;
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
	SDL_GLContext	glcontext;
	SDL_Event		event;
}					t_sdl;;

typedef struct		s_sphere
{
	uint8_t			type;
	t_vec3			center;
	uint8_t			specular;
	float			rad;
	t_color			color;
}					t_sphere;

typedef struct		s_disk
{
	float			t1;
	float			t2;
}					t_disk;

typedef struct		s_conus
{
	t_color			color;
	t_vec3			center;
	u_char			type;
	float			rad;
	float			height;
	t_vec3			mount;
}					t_conus;

typedef struct		s_cam
{
	t_vec3			opoint;
	t_vec3			ray;
	t_vec3			dir;
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
	float			intens;
	uint8_t			type;
	t_color			color;
}					t_light;

typedef struct		s_rt
{
	t_sdl			sdl;
	t_sphere		*sphere;
	t_mouse			mouse;
	t_light			*light;
	t_cam			cam;
	bool			quit;
}					t_rt;

int					main(void);
void				event_list(t_rt *rt);
void				mouse_events(t_rt *rt);
int					which_button(bool *mouse);
t_color				trace_ray(t_cam ray, t_point limit, t_sphere *sphere, t_light *in_light);


int					put_error_sys(char *error);
bool				put_error_sdl(char *error, const char *error_sdl);
bool				init_lib_sdl(t_rt *rt);

float				mod3(t_vec3 vec);
float				multiplication(t_vec3 v1, t_vec3 v2);
float				acos_vec3(t_vec3 v1, t_vec3 v2);
float				dot3(t_vec3 v1, t_vec3 v2);
t_vec3				subtraction3(t_vec3 v1, t_vec3 v2);
t_vec3				addition3(t_vec3 v1, t_vec3 v2);
t_vec3				normalize(t_vec3 vector);
float				clamp(float x, float min, float max);
t_vec3				cross(t_vec3 a, t_vec3 b);
void				clear_surface(SDL_Surface *surface, Uint32 color);
t_vec3				cross_scalar(t_vec3 vect, float scalar);

void				coleidoscope(t_rt *rt, t_point pixel, t_vec3 a);
void				pixel_shader(t_rt *rt, t_point pixel, t_vec3 dir);
void				shading(t_rt *rt);

#endif