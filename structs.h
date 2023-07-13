/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:51:37 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/14 00:18:26 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define WIN_HEIGHT 720
# define WIN_WIDTH 1290
# define PLAYER_SIZE 10
# define PURPLE 0xaa99FF
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define FOV 1.0471975512
# define NB_RAYS WIN_WIDTH
# define PRESSED 1
# define RELEASED 0
# define SCALE_FACTOR 0.2
# define WALL_WIDTH 1
# define HORIZONTAL 0
# define VERTICAL 1
# define SKY	1
# define FLOOR 0
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

typedef struct s_player
{
	double	x;
	double	y;
	int		turn;
	int		walk;
	double	angle;
	int		radius;
	int		speed;
	double	rot_speed;
}	t_player;

typedef struct s_ray
{
	double	x;
	double	y;
	double	angle;
	int		down;
	int		right;
	int		hit;
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
	void	*minimap;
	void	*map_img;
	int		floor_color;
	int		sky_color;
}	t_map;

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_textures
{
	void	*xpm_ptr;
	char	*path;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		ht;
	int		wt;
}	t_textures;

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
	t_textures	t[4];
}	t_mlx;

#endif
