
CC := cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

NAME := cub3D

SRC = main.c helper_functions/helper_functions.c  helper_functions/quee_functions_helper.c  helper_functions/helper_functions1.c  helper_functions/helper_functions2.c  helper_functions/helper_Textures.c  helper_functions/helper_functions3.c helper_functions/helper_functions4.c \
		execution.c minimap.c hdl_mouse.c textures.c player_moves.c player_moves2.c utils.c player_direction.c raycasting.c raycasting2.c utils2.c raycasting3.c minimap2.c

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) -Lmlx_linux -o $(NAME) $(OBJ) libft/libft.a ./mlx_linux/libmlx.a -lXext -lX11 -lm -lz

clean:
	rm -rf $(OBJ)
	make clean -C libft
fclean:
	rm -rf $(NAME) $(OBJ)
	make fclean -C libft

re: fclean all
