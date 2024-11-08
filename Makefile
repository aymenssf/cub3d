
CC := cc

CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux -fsanitize=address -g3
LDFLAGS = libft/libft.a -Lminilibx-linux  -framework OpenGL -framework AppKit  -Iinclude 
NAME := cub3D

SRC = main.c helper_functions/helper_functions.c  helper_functions/quee_functions_helper.c  helper_functions/helper_functions1.c  helper_functions/helper_functions2.c  helper_functions/helper_Textures.c  helper_functions/helper_functions3.c helper_functions/helper_functions4.c \
		execution.c minimap.c

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME) $(OBJ)

re: fclean all
