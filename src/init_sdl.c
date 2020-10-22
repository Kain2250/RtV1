/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 08:30:01 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/21 22:04:49 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

bool			init_sdl(t_rt *rt)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		return (false);
	if ((rt->sdl.window = SDL_CreateWindow(NAME_WIN, 0,
			0, WIN_WIDTH,
			WIN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
		return (false);
	if ((rt->sdl.screen = SDL_GetWindowSurface(rt->sdl.window)) == NULL)
		return (false);
	return (true);
}

bool			init_sdl_image(t_rt *rt)
{
	if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG))
		return (false);
	(void)rt;
	return (true);
}

bool			init_sdl_ttf(t_rt *rt)
{
	if (TTF_Init() == -1)
		return (false);
	(void)rt;
	return (true);
}

bool			init_lib_sdl(t_rt *rt)
{
	if (init_sdl(rt) == false)
		return (put_error_sdl(ERR_INIT_SDL, SDL_GetError()));
	if (init_sdl_image(rt) == false)
		return (put_error_sdl(ERR_INIT_IMG, IMG_GetError()));
	if (init_sdl_ttf(rt) == false)
		return (put_error_sdl(ERR_INIT_TTF, TTF_GetError()));
	return (true);
}
