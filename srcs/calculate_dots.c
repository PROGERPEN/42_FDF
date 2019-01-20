/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_dots.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 17:21:28 by marvin            #+#    #+#             */
/*   Updated: 2019/01/20 17:37:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void iso(int *x, int *y, int z)
{
	int prev_x;
	int prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = -z + (prev_x + prev_y) * sin(0.523599);
}

static void rotate_z(int *x, int *y, double angle)
{
	int prev_x;
	int prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(angle) - prev_y * sin(angle);
	*y = prev_x * sin(angle) + prev_y * cos(angle);
}

static void rotate_x(int *y, int *z, double angle)
{
	int prev_y;
	int prev_z;

	prev_y = *y;
	prev_z = *z;
	*y = prev_y * cos(angle) + prev_z * sin(angle);
	*z = -prev_y * sin(angle) + prev_z * cos(angle);
}

static void rotate_y(int *x, int *z, double angle)
{
	int prev_x;
	int prev_z;

	prev_x = *x;
	prev_z = *z;
	*x = prev_x * cos(angle) + prev_z * sin(angle);
	*z = -prev_x * sin(angle) + prev_z * cos(angle);
}

static void rotate(int *x, int *y, int *z, t_map *map)
{
	rotate_x(y, z, map->x_angle);
	rotate_z(x, y, map->z_angle);
	rotate_y(x, z, map->y_angle);
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
			rotate(&x_coord, &y_coord, &z_coord, map);
			iso(&x_coord, &y_coord, z_coord);
			map->dots[i] = create_dot(x_coord + 1000, y_coord + 500, map->colors[y][x]);
			x++;
			i++;
		}
		y++;
	}
}
