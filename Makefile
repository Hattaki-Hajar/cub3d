SRCS	= $(wildcard ./cub3d/*.c)

BSRCS	= $(wildcard ./cub3d_bonus/*.c)

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

LFLAGS	=	-lmlx -framework OpenGL -framework AppKit #-fsanitize=address -g3

NAME	= Cub3d

BNAME	= Cub3d_bonus

MLX_LIB = ./mlx/libmlx.a

OBJS	= $(SRCS:.c=.o)

BOBJS	= $(BSRCS:.c=.o)

all		: $(NAME)

bonus	: $(BNAME)

.c.o	:
		$(CC) $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJS)
		make -C ./mlx
		$(CC) $(CFLAGS) $(MLX_LIB)  $(SRCS) $(LFLAGS) -o $(NAME)

$(BNAME) : $(BOBJS)
		make -C ./mlx
		$(CC) $(CFLAGS) $(MLX_LIB)  $(BSRCS) $(LFLAGS) -o $(BNAME)

clean	:
		make clean -C ./mlx
		rm -rf $(OBJS) $(BOBJS)

fclean	: clean
		rm -rf $(NAME) $(BNAME)

re		: fclean all