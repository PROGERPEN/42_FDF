/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_draws.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhrazz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 13:09:59 by fkhrazz           #+#    #+#             */
/*   Updated: 2019/01/23 15:03:58 by fkhrazz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			get_color(t_dot *current, t_dot *start, t_dot *end, t_dot *delta)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (start->color == end->color)
		return (start->color);
	if (delta->x > delta->y)
		percentage = percent(start->x, end->x, current->x);
	else
		percentage = percent(start->y, end->y, current->y);
	red = get_light((start->color >> 16) & 0xFF,
			(end->color >> 16) & 0xFF, percentage);
	green = get_light((start->color >> 8) & 0xFF,
			(end->color >> 8) & 0xFF, percentage);
	blue = get_light(start->color & 0xFF, end->color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

void		draw_all_on_image(t_map *map)
{
	int bits_per_pixel;
	int endian;

	if (map->data_addr == NULL)
		ft_strdel(&(map->data_addr));
	map->data_addr = mlx_get_data_addr(map->image, &bits_per_pixel,
			&(map->size_line), &endian);
	calculate_dots(&map);
	draw_lines_on_image(map);
}
