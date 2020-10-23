/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 22:23:21 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/23 22:28:36 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		find_intensity(t_vec3 intersect, t_light *is_light,
							t_vec3 norm, int max_light)
{
	double	intensity;
	int		i;

	intensity = 0;
	i = -1;
	while (++i < max_light)
	{
		if (is_light[i].type == e_ambient)
			intensity += is_light[i].intens;
		else if (is_light[i].type == e_point)
			intensity += light(intersect, is_light[i].dir,
				norm, is_light[i].intens);
		else
			intensity += is_light[i].intens;
	}
	return (clamp(intensity, 0., 1.));
}

t_disk		sphere_intersect(double rad, t_vec3 center,
				t_vec3 cam, t_vec3 direction)
{
	t_vec3	sphere;
	t_disk	point;
	double	diskr;
	t_vec3	cam_center;
	double	disqrt;

	cam_center = subtraction3(cam, center);
	sphere.x = dot3(direction, direction);
	sphere.y = 2. * dot3(cam_center, direction);
	sphere.z = dot3(cam_center, cam_center) - rad * rad;
	diskr = sphere.y * sphere.y - 4. * sphere.x * sphere.z;
	if (diskr < 0)
		return (point = (t_disk){INFINITY, INFINITY});
	disqrt = sqrt(diskr);
	point.t1 = (-sphere.y + disqrt) / (2. * sphere.x);
	point.t2 = (-sphere.y - disqrt) / (2. * sphere.x);
	return (point);
}

t_disk		plane_intersect(t_cam ray, t_vec3 center, t_vec3 norm)
{
	t_disk	point;
	double	a;
	double	b;

	a = dot3(subtraction3(ray.opoint, center), norm);
	b = dot3(ray.dir, norm);
	point.t1 = -(a / b);
	if (point.t1 < 0.)
	point.t1 = INFINITY;
	point.t2 = INFINITY;
	return (point);
}

