SRCS	= $(wildcard ./cub_3d/*.c)

BSRCS	= $(wildcard ./cub_3d_bonus/*.c)

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -pthread

LFLAGS	=	-lmlx -framework OpenGL -framework AppKit #-fsanitize=address -g

NAME	= Cub3D

BNAME	= Cub3D_bonus

MLX_LIB = ./mlx/libmlx.a

OBJS	= $(SRCS:.c=.o)

BOBJS	= $(BSRCS:.c=.o)

all		: $(NAME)

bonus	: $(BNAME)

.c.o	:
		$(CC) $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJS) Makefile
		make -C ./mlx
		$(CC) $(CFLAGS) $(MLX_LIB)  $(SRCS) $(LFLAGS) -o $(NAME)

$(BNAME) : $(BOBJS) Makefile
		make -C ./mlx
		$(CC) $(CFLAGS) $(MLX_LIB)  $(BSRCS) $(LFLAGS) -o $(BNAME)

clean	:
		make clean -C ./mlx
		rm -rf $(OBJS) $(BOBJS)

fclean	: clean
		rm -rf $(NAME) $(BNAME)

re		: fclean all