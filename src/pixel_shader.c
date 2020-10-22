/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_shader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 20:24:57 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/22 05:36:07 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


void				clear_surface(SDL_Surface *surface, Uint32 color)
{
	SDL_LockSurface(surface);
	SDL_memset(surface->pixels, color, surface->h * surface->pitch);//ВАЖНО
	SDL_UnlockSurface(surface);
}

t_color				color32_to_8(uint32_t color)
{
	t_color			color8;

	color8.red = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ?
		(color >> 16) & 0xff : color & 0xff;
	color8.green = (color >> 8) & 0xff;
	color8.blue = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ?
		color & 0xff : (color >> 16) & 0xff;
	return (color8);
}

uint32_t				color8_to_32(t_color color)
{
	if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		return (color.red << 16 | color.green << 8 | color.blue);
	else
		return (color.red | color.green << 8 | color.blue << 16);
}


void				putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int				bpp;
	Uint8			*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		*p = pixel;
	if (bpp == 2)
		*(Uint16 *)p = pixel;
	else if (bpp == 3)
	{
		p[0] = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ?
			(pixel >> 16) & 0xff : pixel & 0xff;
		p[1] = (pixel >> 8) & 0xff;
		p[2] = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ?
			pixel & 0xff : (pixel >> 16) & 0xff;
	}
	else if (bpp == 4)
		*(Uint32 *)p = pixel;
}

t_color		mix_color(t_color color, float intensity)
{
	t_color	mix;

	mix.red = color.red * intensity;
	mix.green = color.green * intensity;
	mix.blue = color.blue * intensity;
	return (mix);
}

float		light(t_vec3 intersect, t_vec3 l_point,
				t_vec3 norm, float intensity)
{
	t_vec3	lvec;

	lvec = normalize(subtraction3(l_point, intersect));
	return (intensity + clamp(dot3(lvec, norm), 0, 1));
}

float		sphere_intersect(float rad, t_vec3 center,
				t_vec3 cam, t_vec3 direction)
{
	t_vec3	sphere;
	float	t1;
	float	t2;
	float	diskr;

	sphere.x = dot3(direction, direction);
	sphere.y = 2.f * dot3(subtraction3(cam, center), direction);
	sphere.z = dot3(subtraction3(cam, center),
		subtraction3(cam, center)) - rad * rad;
	diskr = sphere.y * sphere.y - 4.f * sphere.x * sphere.z;
	if (diskr < 0)
		return (-1.f);
	t1 = (-sphere.y + sqrt(diskr)) / (2.f * sphere.x);
	t2 = (-sphere.y - sqrt(diskr)) / (2.f * sphere.x);
	return (t1 < t2 ? t1 : t2);
}

void		coleidoscope(t_rt *rt, t_point pixel, t_vec3 a)
{
	t_vec3	dir;
	float	t0;
	(void)a;

	float	radius = 20.f;
	t_vec3	center = (t_vec3){.x = 0.f, .y = 0.f, .z = 20.f};
	t_vec3	cam = (t_vec3){.x = 0, .y = 0, .z = 0};
	t_vec3 lp = (t_vec3){.x = 0, .y = 0, .z = 0};;

	dir = normalize(subtraction3(a, cam));
	t0 = sphere_intersect(radius, center, cam, dir);
	if (t0 >= 0)
	{
		
		t_vec3 temp1 = (t_vec3){.x = dir.x * t0, .y = dir.y * t0, .z = dir.z * t0};
		t_vec3 inter = addition3(cam, temp1);
		t_vec3 norm = normalize(subtraction3(inter, center));
		float li = light(inter, lp, norm, 0.08);
		t_color color = (t_color){.red = 200 * li, .green = 100 * li, .blue = 50 * li};
		putpixel(rt->sdl.screen, pixel.x, pixel.y, color8_to_32(color));
	}
}

void		pixel_shader(t_rt *rt, t_point pixel, t_vec3 dir)
{
	float	point;
	float	intensity;
	t_vec3	intersect;
	t_vec3	norm;
	
	point = sphere_intersect(rt->sphere.rad, rt->sphere.center, rt->cam, dir);
	if (point >= 0)
	{
		intersect = addition3(rt->cam, cross_scalar(dir, point));
		norm = normalize(subtraction3(intersect, rt->sphere.center));
		intensity = light(intersect, rt->light, norm, 0.08);
		putpixel(rt->sdl.screen, pixel.x, pixel.y,
			color8_to_32(mix_color(rt->sphere.color, intensity)));
	}
}
