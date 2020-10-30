/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:02:44 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/30 20:04:38 by bdrinkin         ###   ########.fr       */
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
