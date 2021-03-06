/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 02:14:39 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/02 20:54:19 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		mouse_events(t_rt *rt)
{
	if (rt->sdl.event.wheel.type == SDL_MOUSEWHEEL &&
				rt->sdl.event.wheel.y > 0)
		rt->cam.opoint.z += rt->sdl.event.wheel.y * 0.1;
	else if (rt->sdl.event.wheel.type == SDL_MOUSEWHEEL &&
				rt->sdl.event.wheel.y < 0)
		rt->cam.opoint.z += rt->sdl.event.wheel.y * 0.1;
}
