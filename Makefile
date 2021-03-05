# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/14 15:16:41 by jdidier           #+#    #+#              #
#    Updated: 2021/03/04 15:39:32 by jdidier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=cub3D

CC=gcc

CFLAGS= -Wall -Wextra -Werror

FLAGS = -L libft -lft

LFLAGS= -L minilibx-linux -lmlx -lm -lX11 -lXext -lpthread

RM=rm -f

SRCS=main.c gamesystem.c img_color_tools.c parser.c save.c player.c \
trigo_utils.c angle_facing.c raycasting.c sprite.c sprite_utils.c wall.c \
parser_utils.c parser_map.c parser_elements.c error.c check_map.c

SRCS_BONUS=

SRC = $(wildcard *.c)

OBJS=	${SRCS:.c=.o}

BONUS=	${SRCS_BONUS:.c=.o}

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:	${NAME}

${NAME}:	${OBJS}
			$(MAKE) -C minilibx-linux all
			$(MAKE) -C libft all
			${CC} ${CFLAGS} ${OBJS} ${FLAGS} ${LFLAGS} -o ${NAME}

clean:
		$(MAKE) -C libft clean
		$(MAKE) -C minilibx-linux clean
		${RM} ${OBJS} 

fclean: clean
		$(MAKE) -C libft fclean
		${RM} ${NAME}

re: fclean all

.PHONY: clean fclean re