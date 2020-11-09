/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:04:03 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/09 16:26:43 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		keyboard_events(t_rt *rt, SDL_Keycode sym)
{
	if (sym == SDLK_UP || sym == SDLK_DOWN || sym == SDLK_LEFT ||
		sym == SDLK_RIGHT || sym == SDLK_1 || sym == SDLK_2)
	{
		if (sym == SDLK_UP)
			rt->rot.x += 5 * M_PI_180;
		else if (sym == SDLK_DOWN)
			rt->rot.x -= 5 * M_PI_180;
		else if (sym == SDLK_LEFT)
			rt->rot.y -= 5 * M_PI_180;
		else if (sym == SDLK_RIGHT)
			rt->rot.y += 5 * M_PI_180;
		else if (sym == SDLK_1)
			rt->rot.z += 5 * M_PI_180;
		else if (sym == SDLK_2)
			rt->rot.z -= 5 * M_PI_180;
		cache_cam(rt);
	}
}
