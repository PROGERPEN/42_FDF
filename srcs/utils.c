/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 15:47:27 by marvin            #+#    #+#             */
/*   Updated: 2019/01/19 18:10:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int find_index(char base[16], char symb)
{
	int i;

	i = 0;
	while (base[i])
	{
		if (base[i] == symb)
			return (i);
		i++;
	}
	return (-1);
}

/*
**	Функция для получения int цвета из строки
*/

int	color_str_to_int(char *str)
{
	char base[16] = "01234567890ABCDF";
	int res;
	int i;
	int numb;
	int power;

	power = 5;
	res = 0;
	i = 2;
	while (str[i])
	{
		numb = find_index(base, str[i]);
		if (numb == -1)
			return (-1);
		res += numb * pow(16, power);
		i++;
		power--;
	}
	return (res);
}
