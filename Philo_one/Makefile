# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laballea <laballea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 15:19:20 by laballea          #+#    #+#              #
#    Updated: 2021/01/25 09:37:43 by laballea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = #-Wall -Wextra -Werror

SRC = src/buf_utils.c src/ft_utils.c src/ft_utils2.c src/main.c src/monitoring.c

INCLUDE = src/Philosophers.h

OBJ = $(subst .c,.o,$(SRC))

NAME = philo_one

$(NAME): ${OBJ} ${SRC}
	gcc ${CFLAGS} -pthread -lm $(SRC) -o $(NAME)

all: ${NAME}

clean:
	/bin/rm -f ${OBJ}

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : fclean re clean