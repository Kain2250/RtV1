/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:04:03 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/30 20:14:38 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		keyboard_events(t_rt *rt, SDL_Keycode sym)
{
	// if (sym == SDLK_w)
	// 	rt->cam.opoint.z += 0.4;
	// else if (sym == SDLK_s)
	//     rt->cam.opoint.z += 0.4;
	// else if (sym == SDLK_d)
	// 	rt->cam.opoint.x += 0.4;
	// else if (sym == SDLK_a)
	// 	rt->cam.opoint.x -= 0.4;
	// else if (sym == SDLK_e)
	// 	rt->cam.opoint.y -= 0.4;
	// else if (sym == SDLK_q)
	// 	rt->cam.opoint.y += 0.4;	
	// else
    if (sym == SDLK_8)
		rt->light[0].on = !rt->light[0].on;
	else if (sym == SDLK_9)
		rt->light[1].on = !rt->light[1].on;
	else if (sym == SDLK_0)
		rt->light[2].on = !rt->light[2].on;
	else if (sym == SDLK_UP)
	{
		rt->rot[0] += 5 * M_PI_180;
		cache_cam(rt);
	}
	else if (sym == SDLK_DOWN)
	{
		rt->rot[0] -= 5 * M_PI_180;
		cache_cam(rt);
	}
	else if (sym == SDLK_LEFT)
	{
		rt->rot[1] -= 5 * M_PI_180;
		cache_cam(rt);
	}
	else if (sym == SDLK_RIGHT)
	{
		rt->rot[1] += 5 * M_PI_180;
		cache_cam(rt);
	}
		else if (sym == SDLK_1)
	{
		rt->rot[2] += 5 * M_PI_180;
		cache_cam(rt);
	}
	else if (sym == SDLK_2)
	{
		rt->rot[2] -= 5 * M_PI_180;
		cache_cam(rt);
	}
}
