/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 17:48:48 by marvin            #+#    #+#             */
/*   Updated: 2019/01/22 21:40:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	arr_len(char **array)
{
	int i;

	i = 0;
	while(array[i])
		i++;
	return (i);
}

static int count(int *height, int *width, int fd)
{
	char	*line;
	int		lines;
	int		len;
	char	**split_res;
	int		gnl_ret;

	lines = 0;
	len = -1;
	while((gnl_ret = get_next_line(fd, &line)))
	{
		if (gnl_ret == -1)
			return(0);
		lines++;
		split_res = ft_strsplit(line, ' ');
		if (len == -1)
			len = arr_len(split_res);
		if (len != arr_len(split_res))
			return (0);
	}
	*height = lines;
	*width = len;
	return (1);
}

static void read_coord_and_color(char *str, int *coord, int *color)
{
	char **split_res;

	split_res = ft_strsplit(str, ',');
	*coord = ft_atoi(split_res[0]);
	*color = 0xFFFFFF;

	if (split_res[1])
		*color = color_str_to_int(split_res[1]);
}

static int **fill_map(int lines, int symbols, int **colors, int fd)
{
	int		**map;
	char	*line;
	char	**split_res;
	int		y;
	int		x;

	y = 0;
	NULL_CHECK((map = (int **)ft_memalloc(sizeof(int *) * lines)));
	while(get_next_line(fd, &line))
	{
		split_res = ft_strsplit(line, ' ');
		x = 0;
		NULL_CHECK((map[y] = (int *)ft_memalloc(sizeof(int) * symbols)));
		NULL_CHECK((colors[y] = (int *)ft_memalloc(sizeof(int) * symbols)));
		while(x < symbols)
		{
			read_coord_and_color(split_res[x], &(map[y][x]), &(colors[y][x]));
			x++;
		}
		y++;
	}
	return (map);
}

t_map *read_file(char *file_name, void *mlx_ptr, void *win_ptr)
{
	int height;
	int width;
	t_map *map;
	int	fd;

	fd = open(file_name, O_RDONLY);
	height = 0;
	width = 0;
	if (!count(&height, &width, fd))
		return (NULL);
	close(fd);
	fd = open(file_name, O_RDONLY);
	map = create_map(width, height, mlx_ptr, win_ptr);
	map->map = fill_map(height, width, map->colors, fd);
	return (map);
}

