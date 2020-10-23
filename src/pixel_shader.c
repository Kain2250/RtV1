/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_shader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 20:24:57 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/23 22:31:35 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


void				clear_surface(SDL_Surface *surface, Uint32 color)
{
	SDL_LockSurface(surface);
	SDL_memset(surface->pixels, color, surface->h * surface->pitch);//ВАЖНО
	SDL_UnlockSurface(surface);
}

void		color_fill(t_color *dst, t_color src)
{
	dst->red = src.red;
	dst->green = src.green;
	dst->blue = src.blue;
}

t_color		mix_color(t_color color, double intensity)
{
	t_color	mix;

	mix.red = clamp(color.red * intensity, 0, 255);
	mix.green = clamp(color.green * intensity, 0, 255);
	mix.blue = clamp(color.blue * intensity, 0, 255);
	return (mix);
}

double		light(t_vec3 intersect, t_vec3 l_point,
				t_vec3 norm, double intensity)
{
	t_vec3	lvec;

	lvec = normalize(subtraction3(l_point, intersect));
	return (intensity * clamp(dot3(lvec, norm), 0, 1));
}

t_disk		conus_intersect(double rad, t_vec3 center,
				t_vec3 cam, t_vec3 direction)
{
	t_vec3	sphere;
	t_disk	point;
	double	diskr;
	t_vec3	cam_center;
	double	disqrt;

	cam_center = subtraction3(cam, center);
	sphere.x = dot3(direction, direction);
	sphere.y = 2.f * dot3(cam_center, direction);
	sphere.z = dot3(cam_center, cam_center) - rad * rad;
	diskr = sphere.y * sphere.y - 4.f * sphere.x * sphere.z;
	if (diskr < 0)
		return (point = (t_disk){.t1 = INFINITY, .t2 = INFINITY});
	disqrt = sqrt(diskr);
	point.t1 = (-sphere.y + disqrt) / (2.f * sphere.x);
	point.t2 = (-sphere.y - disqrt) / (2.f * sphere.x);
	return (point);
}

t_disk		cylinder_intersect(double rad, t_vec3 center,
				t_vec3 cam, t_vec3 direction)
{
	t_vec3	sphere;
	t_disk	point;
	double	diskr;
	t_vec3	cam_center;
	double	disqrt;

	cam_center = subtraction3(cam, center);
	sphere.x = dot3(direction, direction) - dot3(direction, (t_vec3){0, 1, 0}) * dot3(direction, (t_vec3){0, 1, 0});
	sphere.y = 2.f * dot3(cam_center, direction) - dot3(direction, (t_vec3){0, 1, 0}) * dot3(cam_center, (t_vec3){0, 1, 0});
	sphere.z = dot3(cam_center, (t_vec3){0, 1, 0}) * dot3(cam_center, (t_vec3){0, 1, 0}) - rad * rad;
	diskr = sphere.y * sphere.y - 4.f * sphere.x * sphere.z;
	if (diskr < 0)
		return (point = (t_disk){INFINITY, INFINITY});
	disqrt = sqrt(diskr);
	point.t1 = (-sphere.y + disqrt) / (2.f * sphere.x);
	point.t2 = (-sphere.y - disqrt) / (2.f * sphere.x);
	return (point);
}

t_color		trace_ray(t_cam ray, t_rt *rt, t_shape *shape, t_light *is_light)
{
	t_color	color;
	int		i = 0;
	t_disk	point;
	double	result = INFINITY;
	t_vec3	norm;
	t_vec3	intersect;

	while (i < rt->max_shape)
	{
		if (shape[i].type == e_sphere)
			point = sphere_intersect(shape[i].rad, shape[i].center, ray.opoint, ray.dir);
		// else if (shape[i].type == e_conus)
		// 	point = conus_intersect(shape[i].rad, shape[i].center, ray.opoint, ray.dir);
		// else if (shape[i].type == e_cilindr)
		// 	point = cylinder_intersect(shape[i].rad, shape[i].center, ray.opoint, ray.dir);
		else
			point = plane_intersect(ray, shape[i].center, shape[i].norm);
		if (point.t1 < result && (point.t1 >= rt->limit.x || point.t1 < rt->limit.y))
		{
			result = point.t1;
			color_fill(&color, shape[i].color);
			intersect = addition3(ray.opoint, cross_scalar(ray.dir, result));
			if (shape[i].type == e_plane)
				if (!(mod3(subtraction3(intersect, shape[i].center)) <= shape[i].rad))
					intersect = (t_vec3){INFINITY, INFINITY, INFINITY};
			if (shape[i].type == e_sphere)
				norm = normalize(subtraction3(intersect, shape[i].center));
			// else if (shape[i].type == e_cilindr)
			// 	norm = normalize(subtraction3(subtraction3(intersect, shape[i].center), cross_scalar((t_vec3){0, 1, 0}, result)));
			else if (shape[i].type == e_plane)
				norm = shape[i].norm;
		}
		if (point.t2 < result && (point.t2 >= rt->limit.x || point.t2 < rt->limit.y))
		{
			result = point.t2;
			color_fill(&color, shape[i].color);
			intersect = addition3(ray.opoint, cross_scalar(ray.dir, result));
			if (shape[i].type == e_sphere)
				norm = normalize(subtraction3(intersect, shape[i].center));
			// else if (shape[i].type == e_cilindr)
			// 	norm = normalize(subtraction3(subtraction3(intersect, shape[i].center), cross_scalar((t_vec3){0, 1, 0}, result)));
		}
		i++;
	}
	if (result == INFINITY)
		return ((t_color){0, 0, 0});
	if (intersect.x != INFINITY &&
		intersect.y != INFINITY &&
		intersect.z != INFINITY)
		color = mix_color(color, find_intensity(intersect, is_light, norm, rt->max_light));
	else
		return ((t_color){0, 0, 0});
	return (color);
}

// void		coleidoscope(t_rt *rt, t_point pixel, t_vec3 a)
// {
// 	t_vec3	dir;
// 	double	t0;
// 	(void)a;
// 
// 	double	radius = 20.f;
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
// 		double li = light(inter, lp, norm, 0.08);
// 		t_color color = (t_color){.red = 200 * li, .green = 100 * li, .blue = 50 * li};
// 		SDL_SetRenderDrawColor(rt->sdl.screen, color.red, color.green, color.blue, 0);
// 		SDL_RenderDrawPoint(rt->sdl.screen, pixel.x, pixel.y);
// 
// 		// putpixel(rt->sdl.screen, pixel.x, pixel.y, color8_to_32(color));
// 	}
// }
