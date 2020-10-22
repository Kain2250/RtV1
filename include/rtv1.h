/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:32:46 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/22 04:16:44 by bdrinkin         ###   ########.fr       */
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

# define WIN_WIDTH 700
# define WIN_HEIGHT 700
# define NAME_WIN "RTV by Bdrinkin"
# define SPHERE 0


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
	SDL_Surface		*screen;
	SDL_Event		event;
}					t_sdl;;

typedef struct		s_shape
{
	t_color			color;
	t_vec3			center;
	u_char			type;
	float			rad;
}					t_shape;

typedef struct		s_rt
{
	t_sdl			sdl;
	t_shape			sphere;
	t_mouse			mouse;
	t_vec3			light;
	t_vec3			cam;
	t_vec3			ray;
	bool			quit;
	float			z;
	float			x;
}					t_rt;

int					main(void);
void				event_list(t_rt *rt);
void				mouse_events(t_rt *rt);
int					which_button(bool *mouse);


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


void				pixel_shader(t_rt *rt, t_point pixel);
void				shading(t_rt *rt);

#endif