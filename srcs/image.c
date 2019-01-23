/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 14:27:59 by marvin            #+#    #+#             */
/*   Updated: 2019/01/23 14:44:48 by fkhrazz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_pixel_to_image(char *data_addr, int size_line, t_dot *dot)
{
	int *image;

	image = (int *)data_addr;
	if (dot->x >= 0 && dot->x < IMAGE_WIDTH &&
			dot->y >= 0 && dot->y < IMAGE_HEIGHT)
	{
		image[(size_line / 4) * dot->y + dot->x] = dot->color;
	}
}

static void	line_x(t_dot *dot1, t_dot *dot2, t_dot *delta, t_map *map)
{
	int		d;
	int		i;
	t_dot	*iters;
	t_dot	*huita;
	t_dot	*dot;

	d = (delta->y << 1) - delta->x;
	huita = create_dot(delta->y << 1, (delta->y - delta->x) << 1, 0xFFFFFF);
	iters = create_dot(dot1->x + (dot2->x >= dot1->x ? 1 : -1), dot1->y, W);
	i = 1;
	while (i < delta->x)
	{
		if (d > 0)
		{
			d += huita->y;
			iters->y += (dot2->y >= dot1->y ? 1 : -1);
		}
		else
			d += huita->x;
		dot = create_dot(iters->x, iters->y, 0xFFFFFF);
		dot->color = get_color(dot, dot1, dot2, delta);
		set_pixel_to_image(map->data_addr, map->size_line, dot);
		i++;
		iters->x += (dot2->x >= dot1->x ? 1 : -1);
	}
}

static void	line_y(t_dot *dot1, t_dot *dot2, t_dot *delta, t_map *map)
{
	int		d;
	int		i;
	t_dot	*huita;
	t_dot	*dot;
	t_dot	*iters;

	huita = create_dot(delta->x << 1, (delta->x - delta->y) << 1, W);
	iters = create_dot(dot1->x, dot1->y + (dot2->y >= dot1->y ? 1 : -1), W);
	d = (delta->x << 1) - delta->y;
	i = 1;
	while (i < delta->y)
	{
		if (d > 0)
		{
			d += huita->y;
			iters->x += dot2->x >= dot1->x ? 1 : -1;
		}
		else
			d += huita->x;
		dot = create_dot(iters->x, iters->y, 0xFFFFFF);
		dot->color = get_color(dot, dot1, dot2, delta);
		set_pixel_to_image(map->data_addr, map->size_line, dot);
		i++;
		iters->y += dot2->y >= dot1->y ? 1 : -1;
	}
}

static void	segment(t_dot *dot1, t_dot *dot2, t_map *map)
{
	t_dot *delta;

	delta = create_dot(abs(dot2->x - dot1->x),
			abs(dot2->y - dot1->y), 0xFFFFFF);
	if (delta->y <= delta->x)
		line_x(dot1, dot2, delta, map);
	else
		line_y(dot1, dot2, delta, map);
}

void		draw_lines_on_image(t_map *map)
{
	int i;

	i = -1;
	while (++i < map->height * map->width - 1)
	{
		if ((i + 1) % map->width != 0)
			segment(map->dots[i], map->dots[i + 1], map);
		if (i < (map->height - 1) * map->width)
			segment(map->dots[i], map->dots[i + map->width], map);
	}
}
