/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kain2250 <kain2250@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 08:30:01 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/22 22:22:10 by kain2250         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// bool			init_cl(t_rt *rt)
// {
// 	cl_int			ret;

// 	if (clGetPlatformIDs(1, &rt->cl.platform_id, &rt->cl.num_platform) != 0)
// 		return (false);
// 	if (clGetDeviceIDs(rt->cl.platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &rt->cl.devices_id, rt->cl.num_devices) != 0)
// 		return (false);
// 	rt->cl.context = clCreateContext(NULL, 1, &rt->cl.devices_id, NULL, NULL, &ret);
// 	rt->cl.command_queue = clCreateCommandQueue(rt->cl.context, rt->cl.devices_id, 0, &ret);
// 	return (true);
// }

bool			init_sdl(t_rt *rt)
{
	// if (init_cl(rt))
	// 	return (false);
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return (false);
	if ((rt->sdl.window = SDL_CreateWindow(NAME_WIN, 0,
			0, WIN_WIDTH,
			WIN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)) == NULL)
		return (false);
	if ((rt->sdl.screen = SDL_CreateRenderer(rt->sdl.window, 0,
			SDL_RENDERER_ACCELERATED)) == NULL)
		return (false);
	SDL_SetRelativeMouseMode(true);
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
