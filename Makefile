# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/08 17:22:13 by marvin            #+#    #+#              #
#    Updated: 2019/01/08 17:51:11 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = fdf
FLAGS       = -Wall -Wextra -Werror
SRC_DIR		= ./srcs
OBJ_DIR		= ./obj
CFILES		= main.c get_next_line.c read_file.c map.c
OFILES		= $(CFILES:.c=.o)
RAW_CFILES	= $(addprefix $(SRC_DIR)/,$(CFILES))
RAW_OFILES	= $(addprefix $(OBJ_DIR)/,$(OFILES))

all: $(OBJ_DIR) $(NAME) 
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(NAME): $(RAW_OFILES)
		make -C ./minilibx_macos
		make -C ./libft
		gcc $(RAW_OFILES) libft/libft.a minilibx_macos/libmlx.a -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -I ./includes -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		gcc -Wall -Wextra -Werror -I ./includes -I /usr/local/include -c $< -o $@
clean:
		make clean -C ./minilibx_macos
		make clean -C ./libft
		rm -f $(RAW_OFILES)

fclean: clean 
		make clean -C ./minilibx_macos
		make fclean -C ./libft
		rm -rf $(NAME)

re: fclean all
