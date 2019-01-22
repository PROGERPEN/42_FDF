/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 14:27:59 by marvin            #+#    #+#             */
/*   Updated: 2019/01/22 21:43:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void *create_new_image(t_map *map)
{
	void	*img_ptr;

	img_ptr = mlx_new_image(map->mlx_ptr, IMAGE_WIDTH, IMAGE_HEIGHT);
	return (img_ptr);
}

static void set_pixel_to_image(char *data_addr, int size_line, t_dot *dot)
{
	int *image;

	image = (int *)data_addr;
	if (dot->x >=0 && dot->x < IMAGE_WIDTH && dot->y >= 0 && dot->y < IMAGE_HEIGHT)
	{
		image[(size_line / 4) * dot->y + dot->x] = dot->color;
	}
}

double percent(int start, int end, int current)
{
  double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int get_color(t_dot *current, t_dot *start, t_dot *end, t_dot *delta)
{
	int	 red;
	int	 green;
	int	 blue;
	double  percentage;

	if (start->color == end->color)
		return (start->color);
	if (delta->x > delta->y)
		percentage = percent(start->x, end->x, current->x);
	else
		percentage = percent(start->y, end->y, current->y);
	red = get_light((start->color >> 16) & 0xFF, (end->color >> 16) & 0xFF, percentage);
	green = get_light((start->color >> 8) & 0xFF, (end->color >> 8) & 0xFF, percentage);
	blue = get_light(start->color & 0xFF, end->color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

static void line_x(t_dot *dot1, t_dot *dot2, t_dot *delta, t_map *map)
{
  int   d;
  int   i;
  t_dot *iters;
  t_dot *huita;
  t_dot *dot;

  d = (delta->y << 1) - delta->x;
  huita = create_dot(delta->y << 1, (delta->y - delta->x) << 1, 0xFFFFFF);
  iters = create_dot(dot1->x + (dot2->x >= dot1->x ? 1 : -1),  dot1->y, 0xFFFFFF);
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

static void line_y(t_dot *dot1, t_dot *dot2, t_dot *delta, t_map *map)
{
  int   d;
  int   i;
  t_dot *huita;
  t_dot *dot;
  t_dot *iters;

  huita = create_dot(delta->x << 1, (delta->x - delta->y) << 1, 0xFFFFFF);
  iters = create_dot(dot1->x, dot1->y + (dot2->y >= dot1->y ? 1 : -1), 0xFFFFFF);
  d = (delta->x << 1) - delta->y;
  i = 1;
  while (i < delta->y)
  {
	if ( d >0 )
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

static void segment(t_dot *dot1, t_dot *dot2, t_map *map)
{
  t_dot *delta;

	delta = create_dot(abs(dot2->x - dot1->x), abs(dot2->y - dot1->y), 0xFFFFFF);
	if (delta->y <= delta->x)
		line_x(dot1, dot2, delta, map);
	else
		line_y(dot1, dot2, delta, map);
}

static void draw_lines_on_image( t_map *map)
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

void draw_all_on_image(t_map *map)
{
	int bits_per_pixel;
	int endian;

	if (map->data_addr == NULL)
		ft_strdel(&(map->data_addr));
	map->data_addr = mlx_get_data_addr(map->image, &bits_per_pixel, &(map->size_line), &endian);
  calculate_dots(&map);
	draw_lines_on_image(map);
}
