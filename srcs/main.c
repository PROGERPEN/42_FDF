/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 15:12:02 by marvin            #+#    #+#             */
/*   Updated: 2019/01/20 17:21:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

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

