/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:17:46 by hhattaki          #+#    #+#             */
/*   Updated: 2023/06/24 22:27:34 by hhattaki         ###   ########.fr       */
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
	// printf("%f\n", tan(angle));
	if (t->rays[t->ray].down == -1)
		yin--;
	// printf("yin is == %d \n" , t->rays[t->ray].down);
	// printf("xin is == %f \n" , xstep);
	// printf("%f, %f\n", yin, xin);
	while ((yin >= 0 && yin <= WIN_HEIGHT) && (xin >= 0 && xin <= WIN_WIDTH))
	{
		// printf("loop ...\n");
		if ((angle < t->p.angle - (FOV / 2)) || (angle > t->p.angle + (FOV / 2)))
			break;
		my_mlx_pixel_put(t, xin, yin, 0x00FF0000);
		if (t->map.map[(int)(yin / t->map.tile)][(int)(xin / t->map.tile)] == '1')
		{
			// printf("inside the if condition\n");
			t->rays[t->ray].x_horz_wall = xin ;
			t->rays[t->ray].y_horz_wall = yin;
			my_mlx_pixel_put(t, xin, yin, 0x0000FF00);
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

	xin = roundf(x / t->map.tile) * t->map.tile;
	if (t->rays[t->ray].right == 1)
		xin += t->map.tile;
	yin = roundf(y + (xin - x) * tan(angle));
	xstep = t->map.tile;
	xstep *= t->rays[t->ray].right;
	ystep = t->map.tile * tan(angle);
	if ((t->rays[t->ray].down == -1 && ystep > 0) || (t->rays[t->ray].down == 1 && ystep < 0))
		ystep *= -1;
	if (t->rays[t->ray].right == -1)
		xin--;
	// printf("x: %f y: %f\n", xin, yin);
	while (yin >= 0 && yin <= WIN_HEIGHT && xin >= 0 && xin <= WIN_WIDTH)
	{
		// printf("here %c \n", t->map.map[(int)(yin / t->map.tile)][(int)(xin / t->map.tile)]);
		if (t->map.map[(int)(yin / t->map.tile)][(int)(xin / t->map.tile)] == '1')
		{
			t->rays[t->ray].x_vert_wall = xin;
			t->rays[t->ray].y_vert_wall = yin;
			break ;
		}
		xin += xstep;
		yin += ystep;
		// printf("data xin %f , yin %f , stepx %f , stepy %f \n", xin , yin , xstep , ystep);
	}
}

void	define_wall_distance(double x, double y, t_mlx *t, double angle)
{
	// double	horz_distance;
	// double	vert_distance;

	t->rays[t->ray].down = -1;
	if (angle > 0 && angle < M_PI)
		t->rays[t->ray].down = 1;
	t->rays[t->ray].right = -1;
	if (angle < 0.5 * M_PI || angle > 1.5 * M_PI)
		t->rays[t->ray].right = 1;
	// vertical_wall(x, y, t, angle);
	// my_mlx_pixel_put(t, t->rays[t->ray].x_vert_wall, t->rays[t->ray].y_vert_wall, 0x00FF0000);
	horizontal_wall(x, y, t, angle);
	// exit(1);
	// printf("horz: x: %f, y: %f\n", t->rays[t->ray].x_horz_wall, t->rays[t->ray].y_horz_wall);
	// if (t->rays[t->ray].x_horz_wall != -1)
	// 	horz_distance = calc_distance(x, y
	// 	, t->rays[t->ray].x_horz_wall, t->rays[t->ray].y_horz_wall);
	// else
	// 	horz_distance = SIZE_MAX;
	// if (t->rays[t->ray].x_vert_wall != -1)
	// 	vert_distance = calc_distance(x, y
	// 	, t->rays[t->ray].x_vert_wall, t->rays[t->ray].y_vert_wall);
	// else
	// 	vert_distance = SIZE_MAX;
	// t->rays[t->ray].xwall = t->rays[t->ray].x_horz_wall;
	// t->rays[t->ray].ywall = t->rays[t->ray].y_horz_wall;
	// t->rays[t->ray].wall_distance = horz_distance;
	// if (vert_distance < horz_distance)
	// {
	// 	t->rays[t->ray].xwall = t->rays[t->ray].x_vert_wall;
	// 	t->rays[t->ray].ywall = t->rays[t->ray].y_vert_wall;
	// 	t->rays[t->ray].wall_distance = vert_distance;
	// }
	// printf("final: x-> %f y-> %f\n", t->rays[t->ray].xwall, t->rays[t->ray].ywall);
	// exit (0);
}
