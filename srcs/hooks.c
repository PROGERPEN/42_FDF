/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 15:10:43 by marvin            #+#    #+#             */
/*   Updated: 2019/01/20 16:42:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int key_press(int keycode, t_map *map)
{
	map->image = create_new_image(map);
	if (keycode == 124)
		map->z_angle -= 0.1;
	if (keycode == 123)
		map->z_angle += 0.1;
	if (keycode == 126)
		map->x_angle -= 0.1;
	if (keycode == 125)
		map->x_angle += 0.1;
	return (0);
}

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
	map->image = create_new_image(map);
	if (button == 4)
		map->zoom++;
	if (button == 5 && map->zoom >0)
		map->zoom--;
	return (0);
}

int close_window(void *param)
{
    (void)param;
    exit(0);
    return (0);
}
