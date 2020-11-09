/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 20:38:12 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/04 18:07:45 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3		addition3(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v3;

	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;
	return (v3);
}

t_vec3		cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vec3		cross_scalar(t_vec3 vect, double scalar)
{
	t_vec3	result;

	result.x = vect.x * scalar;
	result.y = vect.y * scalar;
	result.z = vect.z * scalar;
	return (result);
}

t_vec3		normalize(t_vec3 vector)
{
	t_vec3	v1;
	double	lengt;

	lengt = mod3(vector);
	v1.x = vector.x / lengt;
	v1.y = vector.y / lengt;
	v1.z = vector.z / lengt;
	return (v1);
}

double		dot3(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x +
			v1.y * v2.y +
			v1.z * v2.z);
}
