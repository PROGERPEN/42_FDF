/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 15:12:02 by marvin            #+#    #+#             */
/*   Updated: 2019/01/22 21:25:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int draw_on_update(t_map *map)
{
	if (map->prev_image != map->image)
	{
		draw_all_on_image(map);
		if (map->prev_image)
			mlx_destroy_image(map->mlx_ptr, map->prev_image);
		map->prev_image = map->image;
		mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->image, 250, 0);
	}
	return (0);
}

int draw_interface(t_map *map)
{
	mlx_string_put(map->mlx_ptr, map->win_ptr, 10, 10, 0xFFFFFF, "Controls:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 10, 30, 0xFFFFFF, "Scroll up/down - zoom");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 10, 50, 0xFFFFFF, "Arrows - movement");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 10, 70, 0xFFFFFF, "P - change projection");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 10, 90, 0xFFFFFF, "Rotating on numpad:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 30, 110, 0xFFFFFF, "4/1 - x axis");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 30, 130, 0xFFFFFF, "5/2 - y axis");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 30, 150, 0xFFFFFF, "6/3 - z axis");
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
	win_ptr = mlx_new_window(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "test");
	map = read_file(argv[1], mlx_ptr, win_ptr);
	if (!map)
	{
		ft_putstr("Invalid map\n");
		exit(1);
	}
	map->image = create_new_image(map);
	draw_interface(map);
	draw_all_on_image(map);
	mlx_loop_hook(mlx_ptr, &draw_on_update, map);
	mlx_hook(win_ptr, 3, 0, &key_release, map);
	mlx_hook(win_ptr, 2, 0, &key_press, map);
	mlx_hook(win_ptr, 17, 0, &close_window, NULL);
	mlx_hook(win_ptr, 4, 0, &mouse_release, map);
	mlx_loop(mlx_ptr);
}

