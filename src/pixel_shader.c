/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_shader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 20:24:57 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/28 19:28:44 by bdrinkin         ###   ########.fr       */
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

t_color		trace_ray(t_vec3 dir, t_vec3 opoint, t_rt *rt, t_shape *shape, t_light *is_light)
{
	t_color	color;
	int		i = 0;
	t_disk	point;
	double	result = INFINITY;
	t_vec3	norm;
	t_vec3	intersect;
	double	shine = 0;
	double temp = 0;


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
		if (point.t1 < result)// && (point.t1 > rt->limit.x || point.t1 < rt->limit.y))
		{
			result = point.t1;
			color_fill(&color, shape[i].color);
			intersect = addition3(opoint, cross_scalar(dir, result));
			if (shape[i].type == e_plane)
			{
				// if (!(mod3(subtraction3(intersect, shape[i].center)) <= shape[i].rad))
				// 	intersect = (t_vec3){INFINITY, INFINITY, INFINITY};
				norm = shape[i].norm;
			}
			else if (shape[i].type == e_sphere)
				norm = normalize(subtraction3(intersect, shape[i].center));
			else if (shape[i].type == e_cilindr)
			{
				double m = dot3(dir, shape[i].axis) * point.t1 + dot3(subtraction3(opoint, shape[i].center), shape[i].axis);
				norm = normalize(subtraction3(subtraction3(intersect, shape[i].center), cross_scalar(shape[i].axis, m)));
			}
			else if (shape[i].type == e_conus)
			{
				double m = dot3(dir, shape[i].axis) * point.t1 + dot3(subtraction3(opoint, shape[i].center), shape[i].axis);
				norm = normalize(subtraction3(subtraction3(intersect, shape[i].center), cross_scalar(shape[i].axis, m * (1 + shape[i].pow_k))));
			}
		}
		if (point.t2 < result)// && (point.t2 > rt->limit.x || point.t2 < rt->limit.y))
		{
			result = point.t2;
			color_fill(&color, shape[i].color);
			intersect = addition3(opoint, cross_scalar(dir, result));
			if (shape[i].type == e_sphere)
				norm = normalize(subtraction3(intersect, shape[i].center));
			else if (shape[i].type == e_cilindr)
			{
				double m = dot3(dir, shape[i].axis) * point.t2 + dot3(subtraction3(opoint, shape[i].center), shape[i].axis);
				norm = normalize(subtraction3(subtraction3(intersect, shape[i].center), cross_scalar(shape[i].axis, m)));
			}
			else if (shape[i].type == e_conus)
			{
				double m = dot3(dir, shape[i].axis) * point.t2 + dot3(subtraction3(opoint, shape[i].center), shape[i].axis);
				norm = normalize(subtraction3(subtraction3(intersect, shape[i].center), cross_scalar(shape[i].axis, m * (1 + shape[i].pow_k))));
			}
		}
		i++;
	}
	if (result == INFINITY ||
		(intersect.x == INFINITY &&
		intersect.y == INFINITY &&
		intersect.z == INFINITY))
		return ((t_color){0, 0, 0});
	else
	{
		double intensity = find_intensity(intersect, is_light, norm, rt->max_light);
		color = mix_color(color, intensity);
		i = 0;
		while (i < rt->max_light)
		{
			if (rt->light[i].type == e_point && rt->light[i].on == true)
			{
				temp = 0;
				double s = rt->light[i].intens * rt->x;
				if (s != -1)
				{
					t_vec3 lvec = normalize(subtraction3(is_light[i].dir, intersect));
					t_vec3 inv_dir = normalize(cross_scalar(dir, -1.));

					double proj = dot3(lvec, norm);

					t_vec3 a = addition3(cross_scalar(norm, proj), cross_scalar(lvec, -1));
					t_vec3 r = addition3(cross_scalar(norm, proj), a);
					temp = dot3(r, inv_dir);
					shine = pow (temp, s);
				}
				if (temp >= 0.)
				{
					t_vec3 a = (t_vec3){color.red, color.green, color.blue};
					t_vec3 b = (t_vec3){255, 255, 255};

					a = cross_scalar(a, 1. - shine);
					b = cross_scalar(b, shine);

					t_vec3 c = addition3(a, b);
					color = (t_color){c.x, c.y, c.z};
				}
			}
			i++;
		}
		
	}
	return (color);
}

t_disk		disk_of_shapes(t_vec3 dir, t_vec3 opoint, t_shape shape)
{
	t_disk	point;

	if (shape.type == e_sphere)
		point = sphere_intersect(shape, opoint, dir);
	else if (shape.type == e_conus)
		point = conus_intersect(shape, opoint, dir);
	else if (shape.type == e_cilindr)
		point = cylinder_intersect(shape, opoint, dir);
	else
		point = plane_intersect(opoint, dir, shape.center, shape.norm);
	return (point);
}

t_intersect		ray_intersect(t_vec3 dir, t_vec3 opoint,
					t_shape *shape, int count_shape)
{
	int			i;
	t_disk		point;
	double		lengh_ray;
	t_intersect	param;

	i = -1;
	lengh_ray = INFINITY;
	while (++i < count_shape)
	{
		point = disk_of_shapes(dir, opoint, shape[i]);
		if (point.t1 < lengh_ray || point.t2 < lengh_ray)
		{
			if (point.t1 < lengh_ray)
				lengh_ray = point.t1;
			else if (point.t2 < lengh_ray)
				lengh_ray = point.t2;
			else
				continue ;
			param.intersect = addition3(opoint, cross_scalar(dir, lengh_ray));
			param.iter = i;
			param.point = point;
			param.shine = shape->specular;
			color_fill(&param.color, shape[i].color);
		}
	}
	return (param);
}

t_vec3		plane_limiter(t_vec3 intersect, t_shape shape)
{
	if (!(mod3(subtraction3(intersect, shape.center)) <= shape.rad))
		return ((t_vec3){INFINITY, INFINITY, INFINITY});
	return (intersect);
}

t_vec3		surface_norm(t_intersect param, t_shape shape,
				t_vec3 opoint, t_vec3 dir)
{
	t_vec3	norm;
	double	m;

	norm = shape.norm;
	if (shape.type == e_cilindr || shape.type == e_conus)
		m = dot3(dir, shape.axis) *
			param.point.t1 <= param.point.t2 ? param.point.t2 : param.point.t1 +
			dot3(subtraction3(opoint, shape.center), shape.axis);
	if (shape.type == e_sphere)
		norm = normalize(subtraction3(param.intersect, shape.center));
	else if (shape.type == e_cilindr)
		norm = normalize(subtraction3(subtraction3(param.intersect,
			shape.center), cross_scalar(shape.axis, m)));
	else if (shape.type == e_conus)
		norm = normalize(subtraction3(subtraction3(param.intersect,
			shape.center), cross_scalar(shape.axis, m * (1 + shape.pow_k))));
	return (norm);
}

t_color		lighting_calculation(t_intersect param, t_light *light,
				t_vec3 norm, t_vec3 dir)
{
	t_color	color;
	int		i;
	double	proj;
	t_vec3	lvec;
	double	temp;
	t_vec3	a;
	t_vec3	r;
	double	s;
	
	if (param.color.red == 0 && param.color.green == 0 && param.color.blue == 0)
		return ((t_color){0, 0, 0});
	color = mix_color(param.color, find_intensity(param.intersect, light, norm, light->max_light));
	i = 0;
	while (i < light->max_light)
	{
		if (light[i].type == e_point && light[i].on == true)
		{
			temp = 0;
			s = light[i].intens;
			if (s != -1)
			{
				lvec = normalize(subtraction3(light[i].dir, param.intersect));
				proj = dot3(lvec, norm);
				a = addition3(cross_scalar(norm, proj), cross_scalar(lvec, -1));
				r = addition3(cross_scalar(norm, proj), a);
				temp = dot3(r, normalize(cross_scalar(dir, -1.)));
				param.shine = pow (temp, s);
			}
			if (temp >= 0.)
			{
				a = (t_vec3){color.red, color.green, color.blue};
				t_vec3 b = (t_vec3){255, 255, 255};
				a = cross_scalar(a, 1. - param.shine);
				b = cross_scalar(b, param.shine);
				t_vec3 c = addition3(a, b);
				color = (t_color){c.x, c.y, c.z};
			}
		}
		i++;
	}
	return (color);

}

t_color		pixel_shader(t_vec3 dir, t_vec3 opoint, t_rt *rt)
{
	t_intersect	param;
	t_vec3		norm;
	t_color		color;

	param = ray_intersect(dir, opoint, rt->shapes, rt->max_shape);
	norm = surface_norm(param, rt->shapes[param.iter], opoint, dir);
	// color_fill(&color, param.color);
	color = lighting_calculation(param, rt->light, norm, dir);
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
