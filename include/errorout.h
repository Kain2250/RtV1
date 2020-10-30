/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorout.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:59:58 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/30 19:55:50 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROROUT_H
# define ERROROUT_H

# define ERR_FD 2
# define ERR_MALLOC "\033[0;31;1mMemory allocation error\033[0m"
# define ERR_FILE_INVALID "\033[0;31;1mInvalid file\033[0m"
# define ERR_CREATE_WIN "\033[0;31;1mFailed to create window\033[0m"
# define ERR_CREATE_RENDERER "\033[0;31;1mFailed to create renderer\033[0m"

# define ERR_INIT_SDL "\033[0;31;1mFailed to init SDL\033[0m"
# define ERR_EVENT "\033[0;31;1mError SDL Event\033[0m"

# define USAGE_RT "No input scenefile.\n\tUsage: ./rtv1 scene"

#endif
