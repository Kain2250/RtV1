/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:05:58 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/05 18:00:52 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		mod3(t_vec3 vec)
{
	return (sqrt(vec.x * vec.x +
				vec.y * vec.y +
				vec.z * vec.z));
}

double		clamp(double x, double min, double max)
{
	if (x > min && x < max)
		return (x);
	else if (x >= max)
		return (max);
	else if (x <= min)
		return (min);
	return (0);
}

t_vec3		subtraction3(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v3;

	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;
	return (v3);
}

t_vec3		parallel_transfer3(t_vec3 a, t_vec3 b)
{
	return (normalize(subtraction3(a, b)));
}
