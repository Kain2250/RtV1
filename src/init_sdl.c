/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kain2250 <kain2250@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 08:30:01 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/28 11:33:03 by kain2250         ###   ########.fr       */
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
	if ((rt->sdl.window = SDL_CreateWindow(NAME_WIN, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_WIDTH,
			WIN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)) == NULL)
		return (false);
	if ((rt->sdl.screen = SDL_CreateRenderer(rt->sdl.window, 0,
			SDL_RENDERER_ACCELERATED)) == NULL)
		return (false);
	SDL_GetWindowSize(rt->sdl.window, &rt->sdl.win_width, &rt->sdl.win_hight);
	// SDL_SetRelativeMouseMode(true);
	return (true);
}

bool			init_lib_sdl(t_rt *rt)
{
	if (init_sdl(rt) == false)
		return (put_error_sdl(ERR_INIT_SDL, SDL_GetError()));
	return (true);
}
