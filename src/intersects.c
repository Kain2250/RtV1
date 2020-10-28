/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 22:23:21 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/28 19:26:46 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		find_intensity(t_vec3 intersect, t_light *is_light, t_vec3 norm, int max_light)
{
	double	intensity;
	int		i;

	intensity = 0;
	i = -1;
	while (++i < max_light)
	{
		if (is_light[i].on == false)
			continue ;
		if (is_light[i].type == e_ambient)
			intensity += is_light[i].intens;
		else if (is_light[i].type == e_point)
		{
			intensity += light(intersect, is_light[i].dir,
				norm, is_light[i].intens);
		}
		else
			intensity += is_light[i].intens;
	}
	return (clamp(intensity, 0., 1.));
}

t_vec3		equation_variable(t_vec3 direction, t_vec3 cam_center)
{
	t_vec3	equation;

	equation.x = dot3(direction, direction);
	equation.y = 2. * dot3(direction, cam_center);
	equation.z = dot3(cam_center, cam_center);
	return (equation);
}

t_disk		cylinder_intersect(t_shape shape, t_vec3 cam, t_vec3 direction)
{
	t_vec3	x;
	t_vec4	var;
	double	d_v;
	double	d_x;
	double	sq;

	x = subtraction3(cam, shape.center);
	d_v = dot3(direction, shape.axis);
	d_x = dot3(x, shape.axis);
	var.a = dot3(direction, direction) - pow(d_v, 2.);
	var.b = 2 * (dot3(direction, x) - d_v * d_x);
	var.c = dot3(x, x) - pow(d_x, 2.) - shape.rad * shape.rad;
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

t_disk		sphere_intersect(t_shape shape,
				t_vec3 opoint, t_vec3 direction)
{
	t_vec3	sphere;
	t_vec3	cam_center;
	t_disk	point;
	double	diskr[3];

	cam_center = subtraction3(opoint, shape.center);
	sphere = equation_variable(direction, cam_center);
	sphere.z -= shape.rad * shape.rad;
	diskr[0] = sphere.y * sphere.y - 4. * sphere.x * sphere.z;
	if (diskr[0] < 0)
		return (point = (t_disk){INFINITY, INFINITY});
	diskr[1] = sqrt(diskr[0]);
	diskr[2] = 2. * sphere.x;
	point.t1 = (-sphere.y + diskr[1]) / diskr[2];
	point.t2 = (-sphere.y - diskr[1]) / diskr[2];
	return (point);
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

t_disk		plane_intersect(t_vec3 opoint, t_vec3 dir, t_vec3 center, t_vec3 norm)
{
	t_disk	point;
	double	a;
	double	b;

	a = dot3(subtraction3(opoint, center), norm);
	b = dot3(dir, norm);
	point.t1 = -(a / b);
	if (point.t1 < 0.)
		point.t1 = INFINITY;
	point.t2 = INFINITY;
	return (point);
}

