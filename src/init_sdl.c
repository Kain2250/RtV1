/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 08:30:01 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/30 20:01:34 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

bool			init_sdl(t_rt *rt)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return (false);
	if ((rt->sdl.window = SDL_CreateWindow(NAME_WIN, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_WIDTH,
			WIN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
		return (false);
	if ((rt->sdl.screen = SDL_CreateRenderer(rt->sdl.window, 0,
			SDL_RENDERER_ACCELERATED)) == NULL)
		return (false);
	SDL_GetWindowSize(rt->sdl.window, &rt->sdl.win_width, &rt->sdl.win_hight);
	rt->sdl.win_width_old = rt->sdl.win_width;
	rt->sdl.win_hight_old = rt->sdl.win_hight;
	return (true);
}

bool			init_lib_sdl(t_rt *rt)
{
	if (init_sdl(rt) == false)
		return (put_error_sdl(ERR_INIT_SDL, SDL_GetError()));
	return (true);
}
