/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:38:44 by hhattaki          #+#    #+#             */
/*   Updated: 2023/06/17 21:54:24 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "./mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define WIN_HEIGHT 720
# define WIN_WIDTH 1290
# define PLAYER_SIZE 10
# define PURPLE 0xaa99FF
# define WHITE 0xFFFFFF
# define BLACK 0x000000

typedef struct s_player
{
	double	x;
	double	y;
	int		turn;
	double	angle_D;
	double	angle_R;
	int		radius;
}	t_player;

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
}	t_mlx;

int		calc_length_y(int elements_nb);
int		calc_length_x(int elements_nb);
int		move(void	*t);
int		edit_keys(int key, void	*t);
int		edit_keys_2(int key, void	*t);
void	fx(void *t);


