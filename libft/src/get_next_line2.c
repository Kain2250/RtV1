/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kain2250 <kain2250@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 16:26:02 by lmaximin          #+#    #+#             */
/*   Updated: 2019/12/23 22:25:43 by kain2250         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line2.h"
#include "libft.h"

static	t_file_buf	*find_file_buf(int fd, t_list *data_list)
{
	t_file_buf		*temp;
	t_file_buf		*temp_cont;

	temp = NULL;
	while (data_list)
	{
		temp_cont = (t_file_buf*)data_list->content;
		if (temp_cont->fd == fd)
		{
			temp = temp_cont;
			break ;
		}
		data_list = data_list->next;
	}
	return (temp);
}

static int			find_new_line(char **data, char **line, char **buf)
{
	char		*temp_data;
	char		*find_data;
	char		*prev_data;
	int			i;

	i = 0;
	find_data = *data;
	while (find_data[i] != '\n')
		if (!find_data[i++])
			return (0);
	temp_data = &find_data[i];
	*line = ft_strsub(*data, 0, (size_t)i);
	prev_data = *data;
	*data = ft_strdup(temp_data + 1);
	ft_memdel((void*)&prev_data);
	ft_memdel((void*)buf);
	return (1);
}

static int			read_file(int fd, char *buf, t_list **list, char **line)
{
	char			*temp;
	int				ret;
	t_file_buf		*curr_data_struct;

	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if ((curr_data_struct = find_file_buf(fd, *list)))
		{
			temp = curr_data_struct->data;
			curr_data_struct->data = ft_strjoin(temp, buf);
			ft_memdel((void*)&temp);
		}
		else
		{
			curr_data_struct = (t_file_buf*)malloc(sizeof(t_file_buf));
			curr_data_struct->fd = fd;
			curr_data_struct->data = ft_strdup(buf);
			ft_lstadd(list, ft_lstnew(curr_data_struct, sizeof(t_file_buf)));
			ft_memdel((void*)&curr_data_struct);
		}
		buf = ft_memset(buf, 0, BUFF_SIZE + 1);
		if (find_new_line(&(find_file_buf(fd, *list)->data), line, &buf))
			break ;
	}
	return (ret > 0 ? 1 : ret);
}

static void			clean(int fd, t_list **list, char **line, char **buf)
{
	t_file_buf		*temp_cont;
	t_list			*list1;
	t_list			*temp_list;

	list1 = NULL;
	temp_list = *list;
	*line = NULL;
	ft_memdel((void*)buf);
	while (temp_list)
	{
		temp_cont = (t_file_buf*)temp_list->content;
		if (temp_cont == NULL)
			break ;
		if (temp_cont->fd == fd)
		{
			list1 = temp_list;
			ft_memdel((void*)&(temp_cont->data));
			ft_memdel((void*)&temp_cont);
			ft_lstdelitem(list, list1);
			break ;
		}
		temp_list = temp_list->next;
	}
}

int					get_next_line2(const int fd, char **line)
{
	static t_list	*data_list;
	t_file_buf		*cds;
	char			*buf;
	int				ret;

	if (!line || fd < 0 || !(buf = (char *)malloc(sizeof(char) * BUFF_SIZE + 1))
		|| (read(fd, buf, 0) < 0))
		return (-1);
	cds = find_file_buf(fd, data_list);
	if (cds && cds->data && find_new_line(&(cds->data), line, &buf))
		return (1);
	buf = ft_memset(buf, 0, BUFF_SIZE + 1);
	ret = read_file(fd, buf, &data_list, line);
	cds = find_file_buf(fd, data_list);
	if (ret != 0 || cds == NULL || cds->data == NULL || (cds->data)[0] == '\0')
	{
		if (!ret)
			clean(fd, &data_list, line, &buf);
		return (ret);
	}
	*line = cds->data;
	cds->data = NULL;
	ft_memdel((void*)&buf);
	return (1);
}
