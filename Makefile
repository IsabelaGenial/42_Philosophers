NAME				=	philo

SRC_MANDATORY		= 	main.c
OBJ					=	$(SRC_MANDATORY:%.c=%.o)
HEADER				=	philo.h
CC					=	cc
CFLAG				=	-g3 -Wall -Wextra -Werror


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -I. $(OBJ) -o $(NAME)

$(OBJ): $(SRC_MANDATORY)
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

valgrind: all

gdb: all
	gdb --tui ./$(NAME)

.PHONY: all clean fclean re valgrind gdb run directory