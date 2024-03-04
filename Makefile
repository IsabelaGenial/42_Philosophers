# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 13:19:20 by igenial           #+#    #+#              #
#    Updated: 2024/02/26 13:19:22 by igenial          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	philo

SRC_MANDATORY		= 	main.c init.c error.c check.c exec.c waiter.c
OBJ					=	$(SRC_MANDATORY:%.c=%.o)
HEADER				=	./philo.h
CC					=	cc
CFLAG				=	-g3 -Wall -Wextra -Werror -pthread -fsanitize=thread


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAG) -I. $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAG) -I $(HEADER) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

valgrind: all

gdb: all
	gdb --tui ./$(NAME)

.PHONY: all clean fclean re valgrind gdb run directory
