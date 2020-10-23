/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 02:06:02 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/23 18:41:05 by bdrinkin         ###   ########.fr       */
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
		rt->cam.opoint.y -= 1 * 0.1;
	else if (sym == SDLK_s)
		rt->cam.opoint.y += 1 * 0.1;
	else if (sym == SDLK_d)
		rt->cam.opoint.x -= 1 * 0.1;
	else if (sym == SDLK_a)
		rt->cam.opoint.x += 1 * 0.1;
}

void		event_list(t_rt *rt)
{
	while (SDL_PollEvent(&rt->sdl.event) != 0)
	{
		if (event_exit(rt) == true)
			rt->quit = true;
		else if (rt->sdl.event.type == SDL_MOUSEBUTTONDOWN || rt->sdl.event.type == SDL_MOUSEMOTION || rt->sdl.event.wheel.type == SDL_MOUSEWHEEL)
			mouse_events(rt);
		else if (rt->sdl.event.type == SDL_KEYDOWN)
			keyboard_events(rt, rt->sdl.event.key.keysym.sym);
	}
}