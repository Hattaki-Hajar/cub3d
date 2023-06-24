SRCS	= $(wildcard *.c)

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

LFLAGS	=	-lmlx -framework OpenGL -framework AppKit -fsanitize=address -g3

NAME	= cub3d

MLX_LIB = ./mlx/libmlx.a

OBJS	= $(SRCS:.c=.o)

all		: $(NAME)

.c.o	:
		$(CC) $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJS)
		make -C ./mlx
		$(CC) $(CFLAGS) $(MLX_LIB)  $(SRCS) $(LFLAGS) -o $(NAME)

clean	:
		make clean -C ./mlx
		rm -rf $(OBJS)

fclean	: clean
		rm -rf $(NAME)

re		: fclean all