/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:16:23 by marvin            #+#    #+#             */
/*   Updated: 2019/01/08 17:50:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

#include <mlx.h>
#include <math.h>
#include "libft.h"
#include "get_next_line.h"

typedef	struct	s_map
{
	int	width;
	int height;
	int	**map;
}				t_map;

t_map *read_file(char *file_name);
t_map *create_map(int width, int height, int **map_arr);
#endif
