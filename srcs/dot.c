/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 17:13:05 by marvin            #+#    #+#             */
/*   Updated: 2019/01/22 21:40:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_dot *create_dot(int x, int y, int color)
{
	t_dot *dot;

	NULL_CHECK((dot = (t_dot *)ft_memalloc(sizeof(t_dot))));
	dot->x = x;
	dot->y = y;
	dot->color = color;
	return (dot);
}
