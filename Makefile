# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/01 22:25:31 by vfrants           #+#    #+#              #
#    Updated: 2023/10/07 00:23:21 by vfrants          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -g

NAME_S	= server
NAME_C	= client

C_SRC	= client.c
S_SRC	= server.c

C_OBJ	= ${C_SRC:.c=.o}
S_OBJ	= ${S_SRC:.c=.o}

LIBDIR	= ./libft
LIBFT	= ${LIBDIR}/libftprintf.a

LIB		= libft.a

%.o		: %.c
		${CC} ${CFLAGS} -o $@ -c $<

all		: ${NAME_C} ${NAME_S}

${LIBFT}:
		make --no-print-directory -C $(LIBDIR) all

${NAME_C}: ${C_OBJ} ${LIBFT}
		${CC} ${CFLAGS} -o $@ ${C_OBJ} -L . ${LIBFT}

${NAME_S}: ${S_OBJ} ${LIBFT}
		${CC} ${CFLAGS} -o $@ ${S_OBJ} -L . ${LIBFT}

bonus	: ${LIBFT} ${NAME_C} ${NAME_S}

clean	:
		make --no-print-directory -C $(LIBDIR) clean
		${RM} ${LIB} ${C_OBJ} ${S_OBJ}

fclean	: clean
		make --no-print-directory -C $(LIBDIR) fclean
		${RM} ${LIB} ${NAME_S} ${NAME_C}

re		: fclean all

.PHONY: clean flcean all re
