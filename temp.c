	rt->cam.dir = (t_vec3 **)ft_memalloc(sizeof(t_vec3 *) * rt->sdl.win_hight);
	int y = 0;
	while (y < rt->sdl.win_hight)
	{
		int x = 0;
		ray.y = (rt->sdl.win_hight * 0.5 - y) / rt->sdl.win_hight;
		while (x < rt->sdl.win_width)
		{
			rt->cam.dir[y] = (t_vec3 *)ft_memalloc(sizeof(t_vec3) * rt->sdl.win_width);
			ray.x = (x - (rt->sdl.win_width * 0.5)) / rt->sdl.win_hight;
			rt->cam.dir[y][x] = normalize(subtraction3(ray, rt->cam.opoint));
			x++;
		}
		y++;
	}
