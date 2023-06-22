/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:38:44 by hhattaki          #+#    #+#             */
/*   Updated: 2023/06/22 18:18:14 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "./mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define	WIN_HEIGHT 720
# define	WIN_WIDTH 1290
# define	PLAYER_SIZE 10
# define	PURPLE 0xaa99FF
# define	WHITE 0xFFFFFF
# define	BLACK 0x000000
# define	FOV 1.0471975512
# define	NB_RAYS WIN_WIDTH
# define	PRESSED 1
# define	UNPRESSED 0

typedef struct s_player
{
	double	x;
	double	y;
	int		turn;
	int		walk;
	double	angle;
	int		radius;
	double	rot_speed;
}	t_player;

typedef	struct	s_ray
{
	double	x;
	double	y;
}	t_ray;

typedef struct s_map
{
	int		x_elements_nb;
	int		y_elements_nb;
	int		length;
	char	**map;
}	t_map;

typedef	struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_map		map;
	t_player	p;
	t_keys		key;
	t_ray		*rays;
	int			ray;
}	t_mlx;

/*------------calculations------------*/
int		calc_length_y(int elements_nb);
int		calc_length_x(int elements_nb);
void	calc_wall_distance(t_mlx *t, double angle, double x, double y);

/*--------------rendering-------------*/
void	fx(void *t);

/*---------------hooks---------------*/
int		keys_down(int key, void	*t);
int		keys_up(int key, void	*t);

/*---------------moving---------------*/
int		move(void	*t);

/*----------------draw----------------*/
void	draw_square(int x, int y, t_mlx *t, int color, int size);
void	draw_line(t_mlx	*t, double angle, double x, double y);
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);


