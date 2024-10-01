NAME	= cub3D
CC	= cc
SRC	= main.c


%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@


OBJ 	= $(SRC:.c=.o)
all:	$(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -Lmlx_linux mlx_linux/libmlx.a -lXext -lX11 -lm -lz -g3 -fsanitize=address -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)


re:	fclean all
