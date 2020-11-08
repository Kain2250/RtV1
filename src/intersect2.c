/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:05:30 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/08 17:06:28 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3			plane_limiter(t_vec3 intersect, t_shape shape)
{
	if (!(mod3(subtraction3(intersect, shape.center)) <= shape.rad))
		return ((t_vec3){INFINITY, INFINITY, INFINITY});
	return (intersect);
}
