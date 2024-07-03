NAME = fractol

HEADER = fractol.h

CCF = cc -Wall -Wextra -Werror -O3 

SRC = 	fractol.c	 \
		events.c	 \
		render.c	 \
		check_args.c \
		utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CCF) -c $< -o $@

$(NAME): $(OBJ)
	@make -C minilibx-linux
	@$(CCF) -C $^ -Lminilibx-linux -lmlx_Linux -lXext -lX11 -lm  -o $(NAME)

clean:
	@make -C minilibx-linux clean
	@rm -f $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
