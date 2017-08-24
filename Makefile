NAME = fdf
CC = gcc
FLAGS = -Wall -Wextra -Werror -Ofast
ENDFLAGS = -L smlx -lsmlx -L libft -lft -lmlx -lXext -lX11 -lm -lOpenCL -lpthread
SRC = main.c error.c loop.c keys.c flags.c draw.c
OBJ = $(SRC:%.c=src/%.o)

all: $(NAME)

.PHONY: all

%.o: %.c
	$(CC) $(FLAGS) -I include -I libft/include -I smlx/include -o $@ -c $^

$(NAME): $(OBJ)
	make -C libft
	make -C smlx
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(ENDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
