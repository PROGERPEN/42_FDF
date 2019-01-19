/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:38:39 by fmacgyve          #+#    #+#             */
/*   Updated: 2019/01/19 16:36:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# define BUFF_SIZE 100

int							get_next_line(const int fd, char **line);

typedef struct				s_file
{
	int						fd;
	struct s_file			*next;
	char					*temp;
	int						read_res;
}							t_file;

#endif
