/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 14:27:59 by marvin            #+#    #+#             */
/*   Updated: 2019/01/20 16:39:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void *create_new_image(t_map *map)
{
	void	*img_ptr;

	img_ptr = mlx_new_image(map->mlx_ptr, 2000, 1300);
	return (img_ptr);
}

void set_pixel_to_image(char *data_addr, int size_line, t_dot *dot)
{
	int *image;

	image = (int *)data_addr;
	if (dot->x >=0 && dot->x < 2000 && dot->y >= 0 && dot->y < 1300)
	{
		image[(size_line / 4) * dot->y + dot->x] = 0xFFFFFF;
	}
}

void draw_dots_on_image(char *data_addr, t_map *map)
{
	int i;

	calculate_dots(map);
	i = -1;
	while (++i < map->height * map->width)
		set_pixel_to_image(data_addr, map->size_line, map->dots[i]);
}

void segment(int x0, int y0, int x1, int y1, t_map *map, char *data_addr)
{
  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);
  int sx = x1 >= x0 ? 1 : -1;
  int sy = y1 >= y0 ? 1 : -1;

  if (dy <= dx)
  {
    int d = (dy << 1) - dx;
    int d1 = dy << 1;
    int d2 = (dy - dx) << 1;
    for(int x = x0 + sx, y = y0, i = 1; i <= dx; i++, x += sx)
    {
      if ( d >0)
      {
        d += d2;
        y += sy;
      }
      else
        d += d1;
		t_dot *dot = create_dot(x, y, 0xFFFFFF);
    	set_pixel_to_image(data_addr, map->size_line, dot);
    }
  }
  else
  {
    int d = (dx << 1) - dy;
    int d1 = dx << 1;
    int d2 = (dx - dy) << 1;
    for(int y = y0 + sy, x = x0, i = 1; i <= dy; i++, y += sy)
    {
      if ( d >0)
      {
        d += d2;
        x += sx;
      }
      else
        d += d1;
    	t_dot *dot = create_dot(x, y, 0xFFFFFF);
    	set_pixel_to_image(data_addr, map->size_line, dot);
    }
  }
}

void draw_lines_on_image(char *data_addr, t_map *map)
{
	int i;

	i = -1;
	calculate_dots(map);

	while (++i < map->height * map->width - 1)
	{
		if ((i + 1) % map->width != 0)
			segment(map->dots[i]->x, map->dots[i]->y, map->dots[i + 1]->x , map->dots[i + 1]->y, map, data_addr);
		if (i < (map->height - 1) * map->width)
			segment(map->dots[i]->x, map->dots[i]->y, map->dots[i + map->width]->x , map->dots[i + map->width]->y, map, data_addr);

	}
}



void draw_all_on_image(t_map *map)
{
	char *data_addr;
	int bits_per_pixel;
	int endian;

	data_addr = mlx_get_data_addr(map->image, &bits_per_pixel, &(map->size_line), &endian);
	draw_dots_on_image(data_addr, map);
	draw_lines_on_image(data_addr, map);
}
