/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 17:49:38 by marvin            #+#    #+#             */
/*   Updated: 2019/01/09 17:24:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map *create_map(int width, int height, int **map_arr)
{
	t_map *map;

	map = (t_map *)ft_memalloc(sizeof(t_map));
	map->width = width;
	map->height = height;
	map->map = map_arr;
	map->zoom = 10;
	map->mlx_ptr = NULL;
	map->win_ptr = NULL;
	map->dots = (t_dot **)ft_memalloc(sizeof(t_dot *) * width * height);
	return (map);
}