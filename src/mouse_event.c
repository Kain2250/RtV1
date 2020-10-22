/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 02:14:39 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/22 02:16:01 by bdrinkin         ###   ########.fr       */
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
	int		button;

	is_mouse_presed(&rt->mouse);
	button = which_button(&rt->mouse.is_presed);
	if (SDL_BUTTON_RIGHT == button)
		button_rigth_event(rt);
	else if (SDL_BUTTON_LEFT == button)
		button_left_event(rt);
	else if (SDL_BUTTON_MIDDLE == button)
		button_midle_event(rt);
}