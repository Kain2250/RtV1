/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 02:14:39 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/30 19:54:08 by bdrinkin         ###   ########.fr       */
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

}

static void	button_left_event(t_rt *rt)
{
	(void)rt;
}

static void	button_midle_event(t_rt *rt)
{
	(void)rt;
}

void		mouse_events(t_rt *rt)
{
	if (SDL_BUTTON_RIGHT == rt->sdl.event.button.button)
		button_rigth_event(rt);
	else if (SDL_BUTTON_LEFT == rt->sdl.event.button.button)
		button_left_event(rt);
	else if (SDL_BUTTON_MIDDLE == rt->sdl.event.button.button)
		button_midle_event(rt);
	else if (rt->sdl.event.wheel.type == SDL_MOUSEWHEEL &&
				rt->sdl.event.wheel.y > 0)
		rt->cam.opoint.z += rt->sdl.event.wheel.y * 0.1;
	else if (rt->sdl.event.wheel.type == SDL_MOUSEWHEEL &&
				rt->sdl.event.wheel.y < 0)
		rt->cam.opoint.z += rt->sdl.event.wheel.y * 0.1;
}
