/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:38:44 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/08 18:45:36 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "./mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "structs.h"

/*------------calculations------------*/
int		calc_length_y(int elements_nb);
int		calc_length_x(int elements_nb);
double	calc_distance(double x, double y, double xfinal, double yfinal);
double	normalize_angle(double	angle);
void	define_wall_distance(t_mlx *m, double angle);
void	horizontal_wall_inter(t_mlx *m, double angle);
void	vertical_wall_inter(t_mlx *m, double angle);
void	calc_wall_distance(t_mlx *m, double angle, double x, double y);

/*--------------rendering-------------*/
void	cast_rays(t_mlx *m);
void	renderer(void *t);

/*---------------hooks---------------*/
int		keys_down(int key, void	*t);
int		keys_up(int key, void	*t);

/*---------------moving---------------*/
int		move(void	*t);

/*----------------draw----------------*/
void	draw_square(int x, int y, t_mlx *m, int color);
void	draw_line(t_mlx	*m, double angle, double x, double y);
void	draw_ray(t_mlx	*m, double angle, double x, double y);
void	draw_walls(t_mlx	*m);
void	draw_map(t_mlx	*m);
void	draw_player(double x, double y, t_mlx *t, int size);
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);

/*----------window_managment----------*/
int		red_cross(void);
