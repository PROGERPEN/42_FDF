/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 15:12:02 by marvin            #+#    #+#             */
/*   Updated: 2019/01/08 17:49:26 by marvin           ###   ########.fr       */
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

void draw_map(void *mlx_ptr, void *win_ptr, t_map *map)
{
	int x;
	int y;
	int x_coord;
	int y_coord;

	y = 0;
	while (y < map->height) 
	{
		x = 0;
		while (x < map->width)
		{
			x_coord =  x * 30;
			y_coord = y * 30;
			iso(&x_coord, &y_coord, map->map[y][x] * 30);
			mlx_pixel_put(mlx_ptr, win_ptr, x_coord + 1000, y_coord + 500, 0x00FFFFFF);
			x++;
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
	map = read_file(argv[1]);
	draw_map(mlx_ptr, win_ptr, map);

	mlx_loop(mlx_ptr);
}

