/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_shader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kain2250 <kain2250@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 20:24:57 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/23 05:39:03 by kain2250         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


void				clear_surface(SDL_Surface *surface, Uint32 color)
{
	SDL_LockSurface(surface);
	SDL_memset(surface->pixels, color, surface->h * surface->pitch);//ВАЖНО
	SDL_UnlockSurface(surface);
}

t_color		mix_color(t_color color, float intensity)
{
	t_color	mix;

	mix.red = clamp(color.red * intensity, 0, 255);
	mix.green = clamp(color.green * intensity, 0, 255);
	mix.blue = clamp(color.blue * intensity, 0, 255);
	return (mix);
}

float		light(t_vec3 intersect, t_vec3 l_point,
				t_vec3 norm, float intensity)
{
	t_vec3	lvec;

	lvec = normalize(subtraction3(l_point, intersect));
	return (intensity + clamp(dot3(lvec, norm), 0, 1));
}

float		find_intensity(t_cam ray, float result, t_light *is_light, t_vec3 center)
{
	float	intensity;
	t_vec3	intersect;
	t_vec3	norm;
	int		i;

	intensity = 0;
	i = -1;
	while (++i < 2)
	{
		if (is_light[i].type == e_ambient)
			intensity += is_light[i].intens;
		else if (is_light[i].type == e_point)
		{
			intersect = addition3(ray.opoint, cross_scalar(ray.dir, result));
			norm = normalize(subtraction3(intersect, center));
			intensity += light(intersect, is_light[i].dir, norm, is_light[i].intens);
		}
		else
			intensity += is_light[i].intens;
	}
	
	return (clamp(intensity, 0., 1.));
}

t_disk		sphere_intersect(float rad, t_vec3 center,
				t_vec3 cam, t_vec3 direction)
{
	t_vec3	sphere;
	t_disk	point;
	float	diskr;

	sphere.x = dot3(direction, direction);
	sphere.y = 2.f * dot3(subtraction3(cam, center), direction);
	sphere.z = dot3(subtraction3(cam, center),
		subtraction3(cam, center)) - rad * rad;
	diskr = sphere.y * sphere.y - 4.f * sphere.x * sphere.z;
	if (diskr < 0)
		return (point = (t_disk){.t1 = 70000, .t2 = 70000});
	point.t1 = (-sphere.y + sqrt(diskr)) / (2.f * sphere.x);
	point.t2 = (-sphere.y - sqrt(diskr)) / (2.f * sphere.x);
	return (point);
	// return (t1 < t2 ? t1 : t2);
}

// void		coleidoscope(t_rt *rt, t_point pixel, t_vec3 a)
// {
// 	t_vec3	dir;
// 	float	t0;
// 	(void)a;
// 
// 	float	radius = 20.f;
// 	t_vec3	center = (t_vec3){.x = 0.f, .y = 0.f, .z = 20.f};
// 	t_vec3	cam = (t_vec3){.x = 0, .y = 0, .z = 0};
// 	t_vec3 lp = (t_vec3){.x = 0, .y = 0, .z = 0};;
// 
// 	dir = normalize(subtraction3(a, cam));
// 	t0 = sphere_intersect(radius, center, cam, dir);
// 	if (t0 >= 0)
// 	{
// 
// 		t_vec3 temp1 = (t_vec3){.x = dir.x * t0, .y = dir.y * t0, .z = dir.z * t0};
// 		t_vec3 inter = addition3(cam, temp1);
// 		t_vec3 norm = normalize(subtraction3(inter, center));
// 		float li = light(inter, lp, norm, 0.08);
// 		t_color color = (t_color){.red = 200 * li, .green = 100 * li, .blue = 50 * li};
// 		SDL_SetRenderDrawColor(rt->sdl.screen, color.red, color.green, color.blue, 0);
// 		SDL_RenderDrawPoint(rt->sdl.screen, pixel.x, pixel.y);
// 
// 		// putpixel(rt->sdl.screen, pixel.x, pixel.y, color8_to_32(color));
// 	}
// }

void		color_fill(t_color *dst, t_color src)
{
	dst->red = src.red;
	dst->green = src.green;
	dst->blue = src.blue;
}

// t_disk		plane_intersect()
// {
// 	t_disk	point;

// 	return (point);
// }

t_color		trace_ray(t_cam ray, t_point limit, t_shape *shape, t_light *is_light)
{
	t_color	color;
	int		i = -1;
	t_disk	point;
	float	result = 62768.;
	t_vec3	center;

	while (++i != 2)
	{
		if (shape[i].type == e_sphere)
			point = sphere_intersect(shape[i].rad, shape[i].center, ray.opoint, ray.dir);
		// else if (sphere[i].type == e_conus)
		// 	point = conus_intersect(sphere[i].rad, sphere[i].center, ray.opoint, ray.dir);
		// else if (sphere[i].type == e_cilindr)
		// 	point = cilindr_intersect(sphere[i].rad, sphere[i].center, ray.opoint, ray.dir);
		// else
		// 	point = plane_intersect(sphere[i].rad, sphere[i].center, ray.opoint, ray.dir);
		if ((point.t1 >= limit.x || point.t1 <= limit.y) && point.t1 < result)
		{
			result = point.t1;
			color_fill(&color, shape[i].color);
			center = (t_vec3){.x = shape[i].center.x, .y = shape[i].center.y, .z = shape[i].center.z};
		}
		if ((point.t2 >= limit.x || point.t2 <= limit.y) && point.t2 < result)
		{
			result = point.t2;
			color_fill(&color, shape[i].color);
			center = (t_vec3){.x = shape[i].center.x, .y = shape[i].center.y, .z = shape[i].center.z};
		}
	}
	if (result == 62768)
		return (color = (t_color){.red = 0, .green = 0, .blue = 0});
	float intensity = find_intensity(ray, result, is_light, center);
	color = mix_color(color, intensity);
	return (color);
}
