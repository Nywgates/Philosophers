# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laballea <laballea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 15:19:20 by laballea          #+#    #+#              #
#    Updated: 2021/01/25 13:32:28 by laballea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

SRC = src/buf_utils.c src/ft_utils.c src/ft_utils2.c src/main.c

INCLUDE = src/Philosophers.h

OBJ = $(subst .c,.o,$(SRC))

NAME = philo_two

$(NAME): ${OBJ} ${SRC}
	gcc ${CFLAGS} -pthread -lm $(SRC) -o $(NAME)

all: ${NAME}

clean:
	/bin/rm -f ${OBJ}

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : fclean re clean