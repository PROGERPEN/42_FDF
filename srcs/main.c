/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 15:12:02 by marvin            #+#    #+#             */
/*   Updated: 2019/01/09 18:13:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

void iso(int *x, int *y, int z)
{
	int prev_x;
	int prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = -z + (prev_x + prev_y) * sin(0.523599);
}

int draw_dots(t_map *map)
{
	int i;

	i = -1;
	calculate_dots(map);
	mlx_string_put(map->mlx_ptr, map->win_ptr, 0, 0, 0x00FFFFFF, ft_itoa(map->zoom));
	while (++i < map->height * map->width)
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, (map->dots[i])->x + 1000, (map->dots[i])->y + 500, 0x00FFFFFF);
	return (0);
}

void calculate_dots(t_map *map)
{
	int x;
	int y;
	int x_coord;
	int y_coord;
	int i;

	y = 0;
	i = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			x_coord =  x * map->zoom;
			y_coord = y * map->zoom;
			iso(&x_coord, &y_coord, map->map[y][x] * map->zoom);
			map->dots[i] = create_dot(x_coord, y_coord);
			x++;
			i++;
		}
		y++;
	}
}

int main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	*map;

	(void)argc;
	mlx_ptr = NULL;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 2000, 1300, "test");
	map = read_file(argv[1], mlx_ptr, win_ptr);
	mlx_loop_hook(mlx_ptr, &draw_dots, map);
	mlx_hook(win_ptr, 3, 0, &key_release, NULL);
	mlx_hook(win_ptr, 17, 0, &close_window, NULL);
	mlx_hook(win_ptr, 4, 0, &mouse_release, map);
	mlx_loop(mlx_ptr);
}

