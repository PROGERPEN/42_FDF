/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:16:23 by marvin            #+#    #+#             */
/*   Updated: 2019/01/19 19:37:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

#include <mlx.h>
#include <math.h>
#include "libft.h"
#include "get_next_line.h"

typedef struct	s_dot
{
	int			x;
	int			y;
	int			color;
}				t_dot;

typedef	struct	s_map
{
	int			width;
	int			height;
	int			**map;
	int			zoom;
	int			**colors;
	void		*mlx_ptr;
	void		*win_ptr;
	double		z_angle;
	double		x_angle;
	t_dot		**dots;
}				t_map;

t_map	*read_file(char *file_name, void *mlx_ptr, void *win_ptr);
t_map *create_map(int width, int height, void *mlx_ptr, void *win_ptr);
int		close_window(void *param);
int		key_release(int keycode, void *param);
int		key_press(int keycode, t_map *map);
int		mouse_release(int button, int x, int y, t_map *map);
t_dot *create_dot(int x, int y, int color);
void	calculate_dots(t_map *map);
int		erase_dots(t_map *map);
int	color_str_to_int(char *str);
#endif
