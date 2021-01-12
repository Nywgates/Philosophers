# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laballea <laballea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 15:19:20 by laballea          #+#    #+#              #
#    Updated: 2020/09/23 10:27:12 by laballea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra

SRC = src/buf_utils.c src/ft_utils.c src/ft_utils2.c src/main.c

INCLUDE = src/Philosophers.h

OBJ = $(subst .c,.o,$(SRC))

all: ${OBJ}
	gcc -pthread -lm $(SRC) -o philo_one

clean:
	/bin/rm -f ${OBJ}

re: all bonus

.PHONY : fclean re clean