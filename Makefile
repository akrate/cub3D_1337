# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/13 13:17:26 by melkhatr          #+#    #+#              #
#    Updated: 2026/01/09 11:36:29 by melkhatr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = cub3d.c \
       garbage.c \
       utils_pars.c \
       check_pars.c \
       pars_texture.c \
       pars_map.c \
       valid_map.c \
       ft_atoi.c \
       ft_split.c \
       initial.c\
       utils_libft.c \
       utils_sets.c \
       gnl.c \
       utils_valid.c \
       startgame.c \
       clean.c
LDFLAGS = -L./minilibx-linux/ -lmlx_Linux -lXext -lX11

OBJS = $(SRCS:.c=.o)

all: $(NAME)

${NAME}: ${OBJS}
	cd minilibx-linux && ${MAKE}
	${CC} ${CFLAGS} ${OBJS} ${LDFLAGS} -lm -o ${NAME}
%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re