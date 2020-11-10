/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:49:14 by ecelsa            #+#    #+#             */
/*   Updated: 2020/11/10 17:58:36 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int			line_is_text_block(char *sub_line);
int			is_file_valid(char *file_name);
int			blocks_count(char *file_name, int *shapes, int *lights);
int			ft_arrlen(void **arr);
int			iter_block(int block, t_rt *rt);

void		fill_block(int block, t_rt *rt, t_sub_parser sub);
t_vec3		charsplit_to_tvec(char *str, char split);
t_color		charsplit_to_tcolor(char *str, char split);
bool		true_or_false(char *str);
int			type_of_light(char *str);

void		fill_parse_var(t_sub_parser *sub, char *line, char *param);
void		parse_block(int fd, int block, char **line, t_rt *rt);
int			parse_change_block(char *line);
int			parse_fail(char *file_name, t_rt *rt);

#endif
