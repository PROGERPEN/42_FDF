/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_dots.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 17:21:28 by marvin            #+#    #+#             */
/*   Updated: 2019/01/22 21:20:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void transform(int *x, int *y, int z)
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

void calculate_dots(t_map **map)
{
	int x_coord;
	int y_coord;
	int z_coord;
	t_dot *it;

	it = create_dot(-1, -1, 0);
	while (++(it->y) < (*map)->height)
	{
		it->x = -1;
		while (++(it->x) < (*map)->width)
		{
			x_coord = it->x * (*map)->zoom;
			y_coord = it->y * (*map)->zoom;
			z_coord = (*map)->map[it->y][it->x] * (*map)->zoom;
			rotate(&x_coord, &y_coord, &z_coord, *map);
			if ((*map)->iso)
				transform(&x_coord, &y_coord, z_coord);
			if ((*map)->dots[it->color])
				free((*map)->dots[it->color]);
			(*map)->dots[it->color] = create_dot(x_coord + (*map)->movement->x, y_coord + (*map)->movement->y, (*map)->colors[it->y][it->x]);
			it->color++;
		}
	}
	free(it);
}
