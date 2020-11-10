/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 08:33:00 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/10 18:41:20 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	rt_free(t_rt *rt)
{
	if (rt->light)
		free(rt->light);
	if (rt->shapes)
		free(rt->shapes);
	SDL_DestroyRenderer(rt->sdl.screen);
	SDL_DestroyWindow(rt->sdl.window);
	free(rt);
}

double	ft_min_d(double v1, double v2)
{
	return ((v1 < v2) ? v1 : v2);
}

int		put_error_sys(char *error)
{
	ft_putendl_fd(error, ERR_FD);
	return (1);
}

bool	put_error_sdl(char *error, const char *error_sdl)
{
	ft_putstr_fd(error, ERR_FD);
	ft_putchar_fd(' ', ERR_FD);
	ft_putendl_fd(error_sdl, ERR_FD);
	return (false);
}
