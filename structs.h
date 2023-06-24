/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:51:37 by hhattaki          #+#    #+#             */
/*   Updated: 2023/06/24 20:57:02 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# define	WIN_HEIGHT 720
# define	WIN_WIDTH 1290
# define	PLAYER_SIZE 10
# define	PURPLE 0xaa99FF
# define	WHITE 0xFFFFFF
# define	BLACK 0x000000
# define	FOV 1.0471975512
# define	NB_RAYS WIN_WIDTH
# define	PRESSED 1
# define	RELEASED 0

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
	double	angle;
	int		down;
	int		right;
	double	wall_distance;
	double	xwall;
	double	ywall;
	double	x_horz_wall;
	double	y_horz_wall;
	double	x_vert_wall;
	double	y_vert_wall;
}	t_ray;

typedef struct s_map
{
	int		x_elements_nb;
	int		y_elements_nb;
	int		tile;
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
