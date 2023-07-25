/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:51:37 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/25 20:41:56 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define WIN_HEIGHT 720
# define WIN_WIDTH 1290
# define PLAYER_SIZE 10
# define MINI_MAP_HEIGHT 150
# define MINI_MAP_WIDTH 250
# define PURPLE 0xaa99FF
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define FOV 1.0471975512
# define NB_RAYS WIN_WIDTH
# define PRESSED 1
# define RELEASED 0
# define SCALE_FACTOR 0.2
# define HORIZONTAL 0
# define VERTICAL 1
# define FLOOR 0
# define SKY 1
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define DOOR 4

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
	int		hit_door;
	int		vert_hit_door;
	int		horz_hit_door;
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
	int		x_minimap;
	int		y_minimap;
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
	int	space;
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
}	t_texture;

typedef struct s_mouse
{
	int	x;
	int	y;
}	t_mouse;

typedef struct s_door
{
	t_texture	frames[4];
	int			frame;
	// int			x;
	// int			y;
	// int			nb;
}	t_door;

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
	t_mouse		mouse;
	t_texture	t[4];
	t_door		door;
	// int			door_nb;
}	t_mlx;

#endif
