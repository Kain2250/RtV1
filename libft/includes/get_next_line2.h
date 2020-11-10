/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 16:26:10 by lmaximin          #+#    #+#             */
/*   Updated: 2020/11/10 17:06:49 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE2_H
# define GET_NEXT_LINE2_H
# ifndef BUFF_SIZE
#  define BUFF_SIZE 6000
# endif

# include <unistd.h>
# include <stdlib.h>

int				get_next_line2(const int fd, char **line);
typedef struct	s_file_buf
{
	int		fd;
	char	*data;
}				t_file_buf;

#endif
