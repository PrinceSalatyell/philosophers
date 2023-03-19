# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/07 23:04:06 by salatiel          #+#    #+#              #
#    Updated: 2023/03/19 07:43:46 by salatiel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARIABLE DECLARATIONS

SRCS	=	philo.c			\
			utils.c			\
			lib.c			\
			simulation.c	\
			eat.c

OBJS	=	${SRCS:%.c=${DIR_OBJ}%.o}

NAME	=	philo

# DIRECTORIES

DIR_OBJ = objs/

#GCC & FLAGS

CC	=	gcc

42FLAGS	=	-Wall -Werror -Wextra -g -pthread #-fsanitize=address

GCC	=	${CC} ${42FLAGS}

#CLEAN

RM	=	rm -f

#COLORS

COLOUR_GREEN=\033[7;1;32m
COLOUR_END=\033[0m
COLOUR_YELLOW=\033[7;1;33m

# +*+*+**++*+*+*+*+*+*+**+ RULES ++*+**+**++*+*+*+*+*+*+*+*+*+

all:	${NAME}

${NAME}:	${OBJS}
	@${GCC} -o ${NAME} ${OBJS}
	@echo "${COLOUR_GREEN} >>> PHILO OK <<< ${COLOUR_END}"

${DIR_OBJ}%.o:%.c
	@mkdir -p ${dir $@}
	@${CC} ${42FLAGS} -c $< -o $@

clean:
	@${RM} -r ${DIR_OBJ}
	@echo "${COLOUR_YELLOW} >>> OBJS CLEANED <<< ${COLOUR_END}"

fclean:		clean
	@${RM} ${NAME}
	@echo "${COLOUR_YELLOW} >>> ALL CLEANED <<< ${COLOUR_END}"

re:	fclean all

.PHONY:	all clean fclean re libft submodule