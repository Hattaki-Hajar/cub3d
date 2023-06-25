/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:17:46 by hhattaki          #+#    #+#             */
/*   Updated: 2023/06/25 17:06:02 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	horizontal_wall(double x, double y, t_mlx *t, double angle)
{
	double	xin, yin;
	double	ystep, xstep;

	ystep = t->map.tile;
	xstep = t->map.tile / tan(angle);
	yin = floor(y / t->map.tile) * t->map.tile;
	if (t->rays[t->ray].down == 1)
		yin += t->map.tile;
	else
		ystep *= -1; //direction of the step
	if ((t->rays[t->ray].right == -1 && xstep > 0) || (t->rays[t->ray].right == 1 && xstep < 0))
		xstep *= -1;
	xin = x + ((yin - y) / tan(angle));
	if (isnan(xin))
		xin = 0;
	if (t->rays[t->ray].down == -1)
		yin--;
	while ((yin >= 0 && yin <= (t->map.tile * t->map.y_elements_nb)) 
			&& (xin >= 0 && xin <= (t->map.tile * t->map.x_elements_nb)))
	{
		if ((angle < t->p.angle - (FOV / 2)) || (angle > t->p.angle + (FOV / 2)))
			break;
		if (t->map.map[(int)(yin / t->map.tile)][(int)(xin / t->map.tile)] == '1')
		{
			my_mlx_pixel_put(t, xin, yin, 0x0000FF00);
			t->rays[t->ray].x_horz_wall = xin;
			t->rays[t->ray].y_horz_wall = yin;
			// draw_square(xin, yin, t, 0x00FF00, 10);
			break ;
		}
		xin += xstep;
		yin += ystep;
	}
	
}
void	vertical_wall(double x, double y, t_mlx *t, double angle)
{
	double	xin, yin;
	double	ystep, xstep;

	xstep = t->map.tile;
	ystep = t->map.tile * tan(angle);
	xin = floor(x / t->map.tile) * t->map.tile;
	if (t->rays[t->ray].right == 1)
		xin += t->map.tile;
	else
		xstep *= -1;
	yin = y + (xin - x) * tan(angle);
	if (isnan(yin))
		yin = 0;
	if ((t->rays[t->ray].down == -1 && ystep > 0) || (t->rays[t->ray].down == 1 && ystep < 0))
		ystep *= -1;
	if (t->rays[t->ray].right == -1)
		xin--;
	// printf("x: %f y: %f\n", xin, yin);
	while ((yin >= 0 && yin <= (t->map.tile * t->map.y_elements_nb)) 
			&& (xin >= 0 && xin <= (t->map.tile * t->map.x_elements_nb)))
	{
		if (t->map.map[(int)(yin / t->map.tile)][(int)(xin / t->map.tile)] == '1')
		{
			t->rays[t->ray].x_vert_wall = xin;
			t->rays[t->ray].y_vert_wall = yin;
			break ;
		}
		xin += xstep;
		yin += ystep;
	}
}

void	define_wall_distance(double x, double y, t_mlx *t, double angle)
{
	double	horz_distance;
	double	vert_distance;

	t->rays[t->ray].down = -1;
	if (angle > 0 && angle < M_PI)
		t->rays[t->ray].down = 1;
	t->rays[t->ray].right = -1;
	if (angle < M_PI_2 || angle > 3 * M_PI_2)
		t->rays[t->ray].right = 1;
	vertical_wall(x, y, t, angle);
	// my_mlx_pixel_put(t, t->rays[t->ray].x_vert_wall, t->rays[t->ray].y_vert_wall, 0x00FF0000);
	horizontal_wall(x, y, t, angle);
	// exit(1);
	// printf("horz: x: %f, y: %f\n", t->rays[t->ray].x_horz_wall, t->rays[t->ray].y_horz_wall);
	if (t->rays[t->ray].x_horz_wall != -1)
		horz_distance = calc_distance(x, y
		, t->rays[t->ray].x_horz_wall, t->rays[t->ray].y_horz_wall);
	else
		horz_distance = SIZE_MAX;
	if (t->rays[t->ray].x_vert_wall != -1)
		vert_distance = calc_distance(x, y
		, t->rays[t->ray].x_vert_wall, t->rays[t->ray].y_vert_wall);
	else
		vert_distance = SIZE_MAX;
	t->rays[t->ray].xwall = t->rays[t->ray].x_horz_wall;
	t->rays[t->ray].ywall = t->rays[t->ray].y_horz_wall;
	t->rays[t->ray].wall_distance = horz_distance;
	if (vert_distance < horz_distance)
	{
		t->rays[t->ray].xwall = t->rays[t->ray].x_vert_wall;
		t->rays[t->ray].ywall = t->rays[t->ray].y_vert_wall;
		t->rays[t->ray].wall_distance = vert_distance;
	}
	// printf("final: x-> %f y-> %f\n", t->rays[t->ray].xwall, t->rays[t->ray].ywall);
	// exit (0);
}
