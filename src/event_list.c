/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kain2250 <kain2250@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 02:06:02 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/22 23:35:05 by kain2250         ###   ########.fr       */
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

void		keyboard_events(t_rt *rt, SDL_Keycode sym, Uint32 type)
{
	if (sym == SDLK_w && type == SDL_KEYDOWN)
		rt->cam.opoint.y -= 0.2;
	else if (sym == SDLK_s && type == SDL_KEYDOWN)
		rt->cam.opoint.y += 0.2;
	else if (sym == SDLK_d && type == SDL_KEYDOWN)
		rt->cam.opoint.x -= 0.2;
	else if (sym == SDLK_a && type == SDL_KEYDOWN)
		rt->cam.opoint.x += 0.2;
}

void		event_list(t_rt *rt)
{
	while (SDL_PollEvent(&rt->sdl.event) != 0)
	{
		if (event_exit(rt) == true)
			rt->quit = true;
		else
		{
			keyboard_events(rt, rt->sdl.event.key.keysym.sym, rt->sdl.event.type);
			mouse_events(rt);
		}
	}
}