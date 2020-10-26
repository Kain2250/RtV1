/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_shader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 20:24:57 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/26 21:09:54 by bdrinkin         ###   ########.fr       */
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

t_disk		conus_intersect(t_shape shape, t_vec3 opoint, t_vec3 direction)
{
	t_vec3	x;
	t_vec4	var;
	double	d_v;
	double	d_x;
	double	sq;

	x = subtraction3(opoint, shape.center);
	d_v = dot3(direction, shape.axis);
	d_x = dot3(x, shape.axis);
	var.a = dot3(direction, direction) - (1 + shape.pow_k) * pow(d_v, 2);
	var.b = 2 * (dot3(direction, x) - (1 + shape.pow_k) * d_v * d_x);
	var.c = dot3(x, x) - (1 + shape.pow_k) * pow(d_x, 2);
	var.d = var.b * var.b - 4 * var.a * var.c;
	if (var.d < 0)
		return ((t_disk){INFINITY, INFINITY});
	else
	{
		sq = sqrt(var.d);
		return ((t_disk){
		(-var.b + sq) / (2 * var.a),
		(-var.b - sq) / (2 * var.a)});
	}
}

t_color		trace_ray(t_vec3 dir, t_vec3 opoint, t_rt *rt, t_shape *shape, t_light *is_light)
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
			point = sphere_intersect(shape[i], opoint, dir);
		else if (shape[i].type == e_conus)
			point = conus_intersect(shape[i], opoint, dir);
		else if (shape[i].type == e_cilindr)
			point = cylinder_intersect(shape[i], opoint, dir);
		else
			point = plane_intersect(opoint, dir, shape[i].center, shape[i].norm);
		if (point.t1 < result && (point.t1 > rt->limit.x || point.t1 < rt->limit.y))
		{
			result = point.t1;
			color_fill(&color, shape[i].color);
			intersect = addition3(opoint, cross_scalar(dir, result));
			if (shape[i].type == e_plane)
			{
				if (!(mod3(subtraction3(intersect, shape[i].center)) <= shape[i].rad))
					intersect = (t_vec3){INFINITY, INFINITY, INFINITY};
				norm = shape[i].norm;
			}
			else if (shape[i].type == e_sphere)
				norm = normalize(subtraction3(intersect, shape[i].center));
			else if (shape[i].type == e_cilindr)
			{
				double m = dot3(dir, shape[i].axis) * point.t1 + dot3(subtraction3(opoint, shape[i].center), shape[i].axis);
				// if (!(fabs(m) <= 10))
				// 	return ((t_color){0, 0, 0});
				norm = normalize(subtraction3(subtraction3(intersect, shape[i].center), cross_scalar(shape[i].axis, m)));
			}
			else if (shape[i].type == e_conus)
			{
				// return ((t_color){0, 10, 50});
				double m = dot3(dir, shape[i].axis) * point.t1 + dot3(subtraction3(opoint, shape[i].center), shape[i].axis);
				norm = normalize(subtraction3(subtraction3(intersect, shape[i].center), cross_scalar(shape[i].axis, m * (1 + shape[i].pow_k))));
				// norm = normalize(subtraction3(subtraction3(intersect, shape[i].center), cross_scalar(cross_scalar(shape[i].axis, (1 + k * k)), m)));
			}
		}
		if (point.t2 < result && (point.t2 > rt->limit.x || point.t2 < rt->limit.y))
		{
			result = point.t2;
			color_fill(&color, shape[i].color);
			intersect = addition3(opoint, cross_scalar(dir, result));
			if (shape[i].type == e_sphere)
				norm = normalize(subtraction3(intersect, shape[i].center));
			else if (shape[i].type == e_cilindr)
			{
				double m = dot3(dir, shape[i].axis) * point.t2 + dot3(subtraction3(opoint, shape[i].center), shape[i].axis);
				// if (!(fabs(m) <= 5))
				//	return ((t_color){0, 0, 0});
				norm = normalize(subtraction3(subtraction3(intersect, shape[i].center), cross_scalar(shape[i].axis, m)));
			}
			else if (shape[i].type == e_conus)
			{
				// return ((t_color){0, 10, 50});
				double m = dot3(dir, shape[i].axis) * point.t2 + dot3(subtraction3(opoint, shape[i].center), shape[i].axis);
				norm = normalize(subtraction3(subtraction3(intersect, shape[i].center), cross_scalar(shape[i].axis, m * (1 + shape[i].pow_k))));
				// norm = normalize(subtraction3(subtraction3(intersect, shape[i].center), cross_scalar(cross_scalar(shape[i].axis, (1 + k * k)), m)));
			}
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
