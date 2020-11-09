/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 14:40:08 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/09 16:05:35 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>
#include <unistd.h>
#include <stdbool.h>


#define GET_SECTIONS 1
#define GET_PAPARAM 2

#define	SPHERE 1
#define	CYLINDER 2
#define	CONE 3
#define	PLANE 4
#define	LIGHT 5
#define	CAM 6

#define	SPHERE_T "[sphere]"
#define	CYLINDER_T "[cylinder]"
#define	CONE_T "[cone]"
#define	PLANE_T "[plane]"
#define	LIGHT_T "[light]"
#define	CAM_T "[cam]"

# define WIN_WIDTH 600
# define WIN_HEIGHT 600

typedef struct		s_color
{
	uint8_t			red;
	uint8_t			green;
	uint8_t			blue;
}					t_color;

typedef struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct		s_light
{
	int				fil;
	t_vec3			dir;
	double			intens;
	uint8_t			type;
	t_color			color;
	int				max_light;
	bool			on;
}					t_light;

typedef struct		s_shape
{
	int				fil;
	uint8_t			type;
	t_vec3			center;
	double			specular;
	t_vec3			norm;
	t_vec3			axis;
	double			rad;
	t_color			color;
	double			k;
	double			pow_k;
}					t_shape;

typedef struct		s_cam
{
	t_vec3			opoint;
	struct s_vec3	dir[WIN_HEIGHT][WIN_WIDTH];
}					t_cam;

typedef struct		s_rt
{
	// t_sdl			sdl;
	t_shape			*shapes;
	t_light			*light;
	t_cam			cam;
	int				max_shape;
	int				max_light;
	bool			quit;
	double			rot[3];
	int				x;
	int				y;
}					t_rt;

typedef struct		s_sub_parser
{
	t_vec3		opoint;
	t_vec3		dir;
	t_vec3		center;
	t_vec3		axis;
	t_color		color;
	t_vec3		rot;
	double		rad;
	double		specular;
	int			type;
	double		intens;
	bool		on;
}					t_sub_parser;


int	blocks_count(int file_descriptor, int *shapes, int *lights)
{
	char		*line;
	char		*sub_line;
	int			len_line[5];

	*shapes = 0;
	*lights = 0;
	len_line[0] = ft_strlen(SPHERE_T);
	len_line[1] = ft_strlen(CYLINDER_T);
	len_line[2] = ft_strlen(CONE_T);
	len_line[3] = ft_strlen(PLANE_T);
	len_line[4] = ft_strlen(LIGHT_T);
	while ((get_next_line(file_descriptor, &line)))
	{
		sub_line = ft_strtrim(line);
		free(line);
		if ((ft_strncmp(sub_line, SPHERE_T, len_line[0]) == 0) ||
			(ft_strncmp(sub_line,CYLINDER_T, len_line[1]) == 0)
			|| (ft_strncmp(sub_line,CONE_T, len_line[2]) == 0) ||
				(ft_strncmp(sub_line,PLANE_T, len_line[3])) == 0)
			(*shapes)++;
		if ((ft_strncmp(sub_line,LIGHT_T, len_line[4])) == 0)
			(*lights)++;
		free(sub_line);
	}
	lseek(file_descriptor, 0, 0);
	return (1);
}

int ft_arrlen(void **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return(i);
}

void	fill_block(int block, t_rt *rt, t_sub_parser *sub)
{
	int		i;

	if (block == CAM)
		ft_memcpy(&rt->cam.opoint, &sub->opoint, sizeof(t_vec3));
	if (block == LIGHT)
	{
		i = -1;
		while (++i < rt->max_light && rt->light[i].fil != 1);
		rt->light[i].dir = sub->dir;
		rt->light[i].intens = sub->intens;
		rt->light[i].on = sub->on;
		rt->light[i].type = sub->type;
		rt->light[i].max_light = rt->max_light;
		rt->light[i].fil = 1;

	}
}

void 		parse_block(int fd, int block, char **line, t_rt *rt)
{
	char 		*sub_line;
	char		**arr;
	char		**arr_sub;
	int			i;
	t_shape		shape;
	t_sub_parser	sub;


	ft_bzero(&shape, sizeof(t_shape));
	while (get_next_line(fd, line))
	{
		sub_line = ft_strtrim(*line);
		if (sub_line[0] == '[')
		{
			free(sub_line);
			fill_block(block, rt, &sub);
			return ;
		}
		free(*line);
		arr = ft_strsplit(sub_line, '=');
		free(sub_line);
		i = 0;
		if ((ft_arrlen((void **)arr) == 2))
		{
			*line = ft_strtrim(arr[0]);
			if (ft_strequ(*line,"opoint"))
			{
				arr_sub = ft_strsplit(arr[1], ',');
				sub.opoint = (t_vec3){.x = atof(arr_sub[0]) , .y = atof(arr_sub[1]), .z = atof(arr_sub[2])};
				ft_free_split(arr_sub);
			}
			if (ft_strequ(*line,"rot"))
			{
				arr_sub = ft_strsplit(arr[1], ',');
				sub.rot = (t_vec3){.x = atof(arr_sub[0]) , .y = atof(arr_sub[1]), .z = atof(arr_sub[2])};
				ft_free_split(arr_sub);
			}
			else if (ft_strequ(*line,"center"))
			{
				arr_sub = ft_strsplit(arr[1], ',');
				sub.center = (t_vec3){.x = atof(arr_sub[0]) , .y = atof(arr_sub[1]), .z = atof(arr_sub[2])};
				ft_free_split(arr_sub);
			}
			else if (ft_strequ(*line,"axis"))
			{
				arr_sub = ft_strsplit(arr[1], ',');
				sub.axis = (t_vec3){.x = atof(arr_sub[0]) , .y = atof(arr_sub[1]), .z = atof(arr_sub[2])};
				ft_free_split(arr_sub);
			}
			else if (ft_strequ(*line,"color"))
			{
				arr_sub = ft_strsplit(arr[1], ',');
				sub.color = (t_color){.red = arr_sub[0], .green = arr_sub[1], .blue = arr_sub[2]};
				ft_free_split(arr_sub);
			}
			else if (ft_strequ(*line,"rad"))
				sub.rad = atof(arr[1]);		
			else if (ft_strequ(*line,"specular"))
				sub.specular = atof(arr[1]);	
			else if (ft_strequ(*line,"type"))
				sub.type = atof(arr[1]);	
			else if (ft_strequ(*line,"intens"))
				sub.intens = atof(arr[1]);	
			else if (ft_strequ(*line,"on"))
				sub.on = atoi(arr[1]);	
			ft_free_split(arr);
			// if (ft_strncmp(arr[0],"rad",ft_strlen("rad")) == 0)
			// 	shape.rad = atof(arr[1]);
			// else if (ft_strncmp(arr[0],"center",ft_strlen("center")) == 0)
			// {
			// 	arr_sub = ft_strsplit(arr[1], ',');
			// 	if (ft_arrlen((void **)arr_sub) == 3)
			// 		shape.center = (t_vec3) {.x = atof(arr_sub[0]) , .y = atof(arr_sub[1]), .z = atof(arr_sub[2])};
			// 	ft_free_split(arr_sub);
			// }
			// else if (ft_strncmp(arr[0],"color",ft_strlen("color")) == 0)
			// {
			// 	arr_sub = ft_strsplit(arr[1], ',');
			// 	if (ft_arrlen((void **)arr_sub) == 3)
			// 		shape.color = (t_color) {.red = (uint8_t)atoi(arr_sub[0]), .green = (uint8_t)atoi(arr_sub[1]), .blue = (uint8_t)atoi(arr_sub[2])};
			// 	ft_free_split(arr_sub);
			// }

			// else if (ft_strncmp(arr[0],"specular",ft_strlen("specular")) == 0)
			// 	shape.specular = atof(arr[1]);
			// else if (ft_strncmp(arr[0],"rad",ft_strlen("rad")) == 0)
				// shape.rad = atof(arr[1]);
		ft_free_split(arr);
		}
	}
}

int		parse_fail(char *file_name,t_rt *rt)
{
	int		fd;
	char	*line;
	char	*sub_line;
	int		block;

	fd = open(file_name, O_RDONLY);
	blocks_count(fd, &rt->max_shape, &rt->max_light);
	rt->shapes = (t_shape*)malloc(sizeof(t_shape) * rt->max_shape);
	rt->light = (t_light*)malloc(sizeof(t_light) * rt->max_light);
	ft_bzero(rt->shapes,sizeof(t_shape) * rt->max_shape);
	ft_bzero(rt->light,sizeof(t_light) * rt->max_light);
	block = 0;
	while (get_next_line(fd, &line))
	{
		if (block != 0)
			parse_block(fd, block, &line, rt);
		sub_line = ft_strtrim(line);
		block = 0;
		free(line);
		if (ft_strncmp(line,SPHERE_T,ft_strlen(SPHERE_T)) == 0)
			block = SPHERE;
		else if (ft_strncmp(line,CYLINDER_T,ft_strlen(CYLINDER_T)) == 0)
			block = CYLINDER;
		else if (ft_strncmp(line,CONE_T,ft_strlen(CONE_T)) == 0)
			block = CONE;
		else if (ft_strncmp(line,PLANE_T,ft_strlen(PLANE_T)) == 0)
			block = PLANE;
		else if (ft_strncmp(line,LIGHT_T,ft_strlen(LIGHT_T)) == 0)
			block = LIGHT;
		else if (ft_strncmp(line,CAM_T,ft_strlen(CAM_T)) == 0)
			block = CAM;
		free(sub_line);
	}
	return(0);
}



int main()
{
	t_rt	rt;
	parse_fail("map.ini", &rt);
	return(0);
}
