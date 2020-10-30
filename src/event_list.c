/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 02:06:02 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/30 17:49:50 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				which_button(bool *mouse)
{
	*mouse = true;
	if (SDL_BUTTON(SDL_BUTTON_RIGHT) & SDL_GetMouseState(NULL, NULL))
		return (SDL_BUTTON_RIGHT);
	else if (SDL_BUTTON(SDL_BUTTON_LEFT) & SDL_GetMouseState(NULL, NULL))
		return (SDL_BUTTON_LEFT);
	else if (SDL_BUTTON(SDL_BUTTON_MIDDLE) & SDL_GetMouseState(NULL, NULL))
		return (SDL_BUTTON_MIDDLE);
	else if (SDL_BUTTON(SDL_BUTTON_X1) & SDL_GetMouseState(NULL, NULL))
		return (SDL_BUTTON_X1);
	else if (SDL_BUTTON(SDL_BUTTON_X2) & SDL_GetMouseState(NULL, NULL))
		return (SDL_BUTTON_X2);
	*mouse = false;
	return (0);
}

bool			event_exit(t_rt *rt)
{
	if (rt->sdl.event.type == SDL_QUIT ||
		(rt->sdl.event.key.keysym.sym == SDLK_ESCAPE &&
		rt->sdl.event.type == SDL_KEYDOWN))
		return (true);
	else
		return (false);
}

void		keyboard_events(t_rt *rt, SDL_Keycode sym)
{
	if (sym == SDLK_w)
		rt->shapes[0].center.y +=  0.5;
	else if (sym == SDLK_s)
		rt->shapes[0].center.y -= 0.5;
	else if (sym == SDLK_d)
		rt->shapes[0].center.x += 0.5;
	else if (sym == SDLK_a)
		rt->shapes[0].center.x -= 0.5;
	else if (sym == SDLK_e)
		rt->shapes[0].center.z += 0.5;
	else if (sym == SDLK_q)
		rt->shapes[0].center.z -= 0.5;

	else if (sym == SDLK_i)
		rt->light[0].dir.y += 0.9;
	else if (sym == SDLK_k)
		rt->light[0].dir.y -= 0.9;
	else if (sym == SDLK_j)
		rt->light[0].dir.x -= 0.9;
	else if (sym == SDLK_l)
		rt->light[0].dir.x += 0.9;
	else if (sym == SDLK_u)
		rt->light[0].dir.z -= 0.9;
	else if (sym == SDLK_o)
		rt->light[0].dir.z += 0.9;
	
	else if (sym == SDLK_8)
		rt->light[0].on = !rt->light[0].on;
	else if (sym == SDLK_9)
		rt->light[1].on = !rt->light[1].on;
	else if (sym == SDLK_0)
		rt->light[2].on = !rt->light[2].on;

	else if (sym == SDLK_t)
		rt->cam.opoint.y += 0.4;
	else if (sym == SDLK_g)
		rt->cam.opoint.y -= 0.4;
	else if (sym == SDLK_f)
		rt->cam.opoint.x += 0.4;
	else if (sym == SDLK_h)
		rt->cam.opoint.x -= 0.4;
	else if (sym == SDLK_r)
		rt->cam.opoint.z += 0.4;
	else if (sym == SDLK_y)
		rt->cam.opoint.z -= 0.4;

	else if (sym == SDLK_1)
	{
		rt->rot[0] += M_PI_180;
		cache_cam(rt);
	}
	else if (sym == SDLK_2)
	{
		rt->rot[0] -= 5 * M_PI_180;
		cache_cam(rt);
	}
	else if (sym == SDLK_3)
	{
		rt->rot[1] += 5 * M_PI_180;
		cache_cam(rt);
	}
	else if (sym == SDLK_4)
	{
		rt->rot[1] -= 5 * M_PI_180;
		cache_cam(rt);
	}
		else if (sym == SDLK_5)
	{
		rt->rot[2] += 5 * M_PI_180;
		cache_cam(rt);
	}
	else if (sym == SDLK_6)
	{
		rt->rot[2] -= 5 * M_PI_180;
		cache_cam(rt);
	}
}

void		event_list(t_rt *rt)
{
	while (SDL_PollEvent(&rt->sdl.event) != 0)
	{
		if (event_exit(rt) == true)
			rt->quit = true;
		else if (rt->sdl.event.type == SDL_MOUSEBUTTONDOWN ||
			rt->sdl.event.type == SDL_MOUSEMOTION ||
			rt->sdl.event.wheel.type == SDL_MOUSEWHEEL)
			mouse_events(rt);
		else if (rt->sdl.event.type == SDL_KEYDOWN)
			keyboard_events(rt, rt->sdl.event.key.keysym.sym);
	}
}