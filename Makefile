# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 10:39:42 by bgoron            #+#    #+#              #
#    Updated: 2024/11/28 19:33:41 by bgoron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = clang
CFLAGS = -Wall -Werror -Wextra -O3 -IMacroLibX/includes -Iinc

SRCS = src/main.c \
src/ft_utils.c \
src/ft_map.c \
src/ft_color.c \
src/ft_hook.c \
src/ft_set.c \
src/ft_screen.c \
src/ft_input.c \

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ ./MacroLibX/libmlx.so -lSDL2 -lm

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

all: $(NAME)

.PHONY: all clean fclean re
