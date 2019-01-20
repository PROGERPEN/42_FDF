/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 15:12:02 by marvin            #+#    #+#             */
/*   Updated: 2019/01/20 16:37:20 by marvin           ###   ########.fr       */
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

/*int draw_lines(t_map *map)
{
	int i;

	i = -1;
	calculate_dots(map);

	while (++i < map->height * map->width - 1)
	{
		if ((i + 1) % map->width != 0)
			segment(map->dots[i]->x, map->dots[i]->y, map->dots[i + 1]->x , map->dots[i + 1]->y, map);
		if (i < (map->height - 1) * map->width)
			segment(map->dots[i]->x, map->dots[i]->y, map->dots[i + map->width]->x , map->dots[i + map->width]->y, map);

	}
	return (0);
}

int draw_dots(t_map *map)
{
	int i;

	i = -1;

	calculate_dots(map);
	mlx_string_put(map->mlx_ptr, map->win_ptr, 0, 0, 0x00FFFFFF, ft_itoa(map->zoom));
	while (++i < map->height * map->width)
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, (map->dots[i])->x, (map->dots[i])->y, (map->dots[i])->color);
	return (0);
}

int draw_all(t_map *map)
{
	calculate_dots(map);
	draw_lines(map);
	draw_dots(map);
	return (0);
}*/

void rotate_z(int *x, int *y, double angle)
{
	int prev_x;
	int prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(angle) - prev_y * sin(angle);
	*y = prev_x * sin(angle) + prev_y * cos(angle);
}

void rotate_x(int *y, int *z, double angle)
{
	int prev_y;
	int prev_z;

	prev_y = *y;
	prev_z = *z;
	*y = prev_y * cos(angle) + prev_z * sin(angle);
	*z = -prev_y * sin(angle) + prev_z * cos(angle);
}

void calculate_dots(t_map *map)
{
	int x;
	int y;
	int x_coord;
	int y_coord;
	int i;
	int z_coord;

	y = 0;
	i = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			x_coord =  x * map->zoom;
			y_coord = y * map->zoom;
			z_coord = map->map[y][x] * map->zoom;
			rotate_z(&x_coord,  &y_coord, map->z_angle);
			rotate_x(&y_coord, &z_coord, map->x_angle);
			iso(&x_coord, &y_coord, z_coord);
			map->dots[i] = create_dot(x_coord + 1000, y_coord + 500, map->colors[y][x]);
			x++;
			i++;
		}
		y++;
	}
}

int draw_on_update(t_map *map)
{
	if (map->prev_image != map->image)
	{
		draw_all_on_image(map);
		if (map->prev_image)
			mlx_destroy_image(map->mlx_ptr, map->prev_image);
		map->prev_image = map->image;
		mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->image, 0, 0);
	}
	return (0);
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
	map->image = create_new_image(map);
	draw_all_on_image(map);
	mlx_loop_hook(mlx_ptr, &draw_on_update, map);
	mlx_hook(win_ptr, 3, 0, &key_release, map);
	mlx_hook(win_ptr, 2, 0, &key_press, map);
	mlx_hook(win_ptr, 17, 0, &close_window, NULL);
	mlx_hook(win_ptr, 4, 0, &mouse_release, map);
	mlx_loop(mlx_ptr);
}

