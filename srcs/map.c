/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 17:49:38 by marvin            #+#    #+#             */
/*   Updated: 2019/01/08 17:51:47 by marvin           ###   ########.fr       */
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
	return (map);
}
