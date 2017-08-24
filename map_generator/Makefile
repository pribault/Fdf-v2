NAME = map_generator
CC = gcc
FLAGS = -Wall -Wextra
SRC = main.c
OBJ = $(SRC:%.c=src/%.o)

all: $(NAME)

.PHONY: all clean fclean re

%.o: %.c
	$(CC) $(FLAGS) -I include -o $@ -c $^

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) -lft

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
