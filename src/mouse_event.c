/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 02:14:39 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/25 19:02:15 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		is_mouse_presed(t_mouse *mouse)
{
	if (mouse->is_presed == false)
		SDL_GetMouseState(&mouse->prew_x, &mouse->prew_y);
	else
		SDL_GetMouseState(&mouse->x, &mouse->y);
}

static void	button_rigth_event(t_rt *rt)
{
	(void)rt;
	// if (rt->sdl.event.type == SDL_MOUSEMOTION)
	// {
	// 	rt->shapes[0].center.x += atan(rt->sdl.event.motion.xrel);
	// 	rt->shapes[0].center.y -= atan(rt->sdl.event.motion.yrel);
	// 	// rt->shapes[0].center.z += atan(rt->sdl.event.motion.yrel);
	// 	// rt->shapes[0].center.y++;
	// }

}

static void	button_left_event(t_rt *rt)
{
	(void)rt;
	if (rt->sdl.event.type == SDL_MOUSEMOTION)
	{
		rt->cam.opoint.x += atan(rt->sdl.event.motion.xrel);
	}
}

static void	button_midle_event(t_rt *rt)
{
	(void)rt;
	// if (rt->sdl.event.wheel.type == SDL_MOUSEWHEEL && rt->sdl.event.wheel.y > 0)
	// 	rt->shapes[1].norm.z += rt->sdl.event.wheel.y * 0.01;
	// else if (rt->sdl.event.wheel.type == SDL_MOUSEWHEEL && rt->sdl.event.wheel.y < 0)
	// 	rt->shapes[1].norm.z += rt->sdl.event.wheel.y * 0.01;
}

void		mouse_events(t_rt *rt)
{
	if (SDL_BUTTON_RIGHT == rt->sdl.event.button.button)
		button_rigth_event(rt);
	else if (SDL_BUTTON_LEFT == rt->sdl.event.button.button)
		button_left_event(rt);
	else if (SDL_BUTTON_MIDDLE == rt->sdl.event.button.button)
		button_midle_event(rt);
	else if (rt->sdl.event.wheel.type == SDL_MOUSEWHEEL && rt->sdl.event.wheel.y > 0)
		rt->cam.opoint.z += rt->sdl.event.wheel.y * 0.01;
	else if (rt->sdl.event.wheel.type == SDL_MOUSEWHEEL && rt->sdl.event.wheel.y < 0)
		rt->cam.opoint.z += rt->sdl.event.wheel.y * 0.01;
}
