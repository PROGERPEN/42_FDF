/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:16:23 by marvin            #+#    #+#             */
/*   Updated: 2019/01/23 15:47:09 by fkhrazz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

# include <mlx.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"

# define WINDOW_HEIGHT		1400
# define WINDOW_WIDTH	2400
# define IMAGE_HEIGHT		1300
# define IMAGE_WIDTH		2300
# define NULL_CHECK(val) if (val == NULL) exit(12);
# define W 0xFFFFFF

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
	void		*image;
	void		*prev_image;
	int			size_line;
	double		z_angle;
	double		x_angle;
	double		y_angle;
	char		*data_addr;
	int			iso;
	t_dot		*movement;
	t_dot		**dots;
}				t_map;

t_map			*read_file(char *file_name, void *mlx_ptr, void *win_ptr);
t_map			*create_map(int width, int height,
		void *mlx_ptr, void *win_ptr);
int				close_window(void *param);
int				key_release(int keycode, void *param);
int				key_press(int keycode, t_map *map);
int				mouse_release(int button, int x, int y, t_map *map);
t_dot			*create_dot(int x, int y, int color);
void			calculate_dots(t_map **map);
int				erase_dots(t_map *map);
void			*create_new_image(t_map *map);
int				color_str_to_int(char *str);
void			draw_all_on_image(t_map *map);
void			transform(int *x, int *y, int z);
void			*create_new_image(t_map *map);
double			percent(int start, int end, int current);
int				get_light(int start, int end, double percentage);
int				get_color(t_dot *current, t_dot *start,
		t_dot *end, t_dot *delta);
int				get_light(int start, int end, double percentage);
int				get_color(t_dot *current, t_dot *start,
		t_dot *end, t_dot *delta);
void			draw_all_on_image(t_map *map);
void			draw_lines_on_image(t_map *map);
#endif
