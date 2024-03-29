/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 17:49:38 by marvin            #+#    #+#             */
/*   Updated: 2019/01/23 11:53:54 by fkhrazz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*create_map(int width, int height, void *mlx_ptr, void *win_ptr)
{
	t_map *map;

	NULL_CHECK((map = (t_map *)ft_memalloc(sizeof(t_map))));
	map->width = width;
	map->height = height;
	NULL_CHECK((map->map = (int **)ft_memalloc(sizeof(int *) * height)));
	map->zoom = 10;
	map->z_angle = 0;
	map->x_angle = 0;
	map->y_angle = 0;
	map->size_line = 0;
	map->iso = 1;
	map->data_addr = NULL;
	NULL_CHECK((map->colors = (int **)ft_memalloc(sizeof(int *) * height)));
	map->mlx_ptr = mlx_ptr;
	map->win_ptr = win_ptr;
	map->movement = create_dot(IMAGE_WIDTH / 2, IMAGE_HEIGHT / 2, 0xFFFFFF);
	NULL_CHECK((map->dots = (t_dot **)ft_memalloc(sizeof(t_dot *)
					* width * height)));
	return (map);
}
