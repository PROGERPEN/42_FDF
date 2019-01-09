/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 15:10:43 by marvin            #+#    #+#             */
/*   Updated: 2019/01/09 17:52:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int key_release(int keycode, void *param)
{
	if (keycode == 53)
		close_window(param);
	return (0);
}

int mouse_release(int button, int x, int y, t_map *map)
{
	(void)x;
	(void)y;
	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	if (button == 4)
		map->zoom++;
	if (button == 5)
		map->zoom--;
	return (0);
}

int close_window(void *param)
{
    (void)param;
    exit(0);
    return (0);
}
