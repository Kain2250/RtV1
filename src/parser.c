#include "rtv1.h"

#define	SPHERE 1
#define	CILINDER 2
#define	CONE 3
#define	PLANE 4
#define	LIGHT 5

t_shape *parse_fail(char *file_name)
{
	int		fd;
	int		fr;
	char	*line;
	t_shape	*shape;
	int block;


	fd = open(file_name, O_RDONLY);
	while (fr = get_next_line(fd, &line))
	{
		if (block)
		{

		}
		free(line);
	}
	return(NULL);
}