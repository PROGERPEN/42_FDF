/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 17:48:48 by marvin            #+#    #+#             */
/*   Updated: 2019/01/08 17:52:00 by marvin           ###   ########.fr       */
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

	lines = 0;
	len = -1;
	while(get_next_line(fd, &line))
	{
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


static int **fill_map(int lines, int symbols, int fd)
{
	int		**map;
	char	*line;
	char	**split_res;
	int		y;
	int		x;

	y = 0;
	map = (int **)ft_memalloc(sizeof(int *) * lines);
	while(get_next_line(fd, &line))
	{
		split_res = ft_strsplit(line, ' ');
		x = 0;
		map[y] = (int *)ft_memalloc(sizeof(int) * symbols);
		while(x < symbols)
		{
			map[y][x] = ft_atoi(split_res[x]);
			x++;
		}
		y++;
	}
	return (map);
}

t_map *read_file(char *file_name)
{
	int height;
	int width;
	int	**map_arr;
	t_map *map;
	int	fd;

	fd = open(file_name, O_RDONLY);
	height = 0;
	width = 0;
	if (!count(&height, &width, fd))
		return (0);
	close(fd);
	fd = open(file_name, O_RDONLY);
	map_arr = fill_map(height, width, fd);
	map = create_map(width, height, map_arr);
	return (map);
}

