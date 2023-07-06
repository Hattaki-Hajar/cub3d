/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:17:46 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/06 20:01:22 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	horizontal_wall(double x, double y, t_mlx *m, double angle)
{
	double	xin, yin;
	double	ystep, xstep;

	ystep = m->map.tile;
	xstep = m->map.tile / tan(angle);
	yin = floor(y / m->map.tile) * m->map.tile;
	if (m->rays[m->ray].down == 1)
		yin += m->map.tile;
	else
		ystep *= -1; //direction of the step.
	if ((m->rays[m->ray].right == -1 && xstep > 0)
		|| (m->rays[m->ray].right == 1 && xstep < 0))
		xstep *= -1;
	xin = x + ((yin - y) / tan(angle));
	if (isnan(xin))
		xin = 0;
	if (m->rays[m->ray].down == -1)
		yin--;
	while ((yin >= 0 && yin <= (m->map.tile * m->map.y_elements_nb)) 
			&& (xin >= 0 && xin <= (m->map.tile * m->map.x_elements_nb)))
	{
		if ((angle < m->p.angle - (FOV / 2)) || (angle > m->p.angle + (FOV / 2)))
			break;
		if (m->map.map[(int)(yin / m->map.tile)][(int)(xin / m->map.tile)] == '1')
		{
			m->rays[m->ray].x_horz_wall = xin;
			m->rays[m->ray].y_horz_wall = yin;
			return ;
		}
		xin += xstep;
		yin += ystep;
	}
}

void	vertical_wall(double x, double y, t_mlx *m, double angle)
{
	double	xin, yin;
	double	ystep, xstep;

	xstep = m->map.tile;
	ystep = m->map.tile * tan(angle);
	xin = floor(x / m->map.tile) * m->map.tile;
	if (m->rays[m->ray].right == 1)
		xin += m->map.tile;
	else
		xstep *= -1;
	yin = y + ((xin - x) * tan(angle));
	if (isnan(yin))
		yin = 0;
	if ((m->rays[m->ray].down == -1 && ystep > 0) || (m->rays[m->ray].down == 1 && ystep < 0))
		ystep *= -1;
	if (m->rays[m->ray].right == -1)
		xin--;
	while ((yin >= 0 && yin <= (m->map.tile * m->map.y_elements_nb)) 
			&& (xin >= 0 && xin <= (m->map.tile * m->map.x_elements_nb)))
	{
		if ((angle < m->p.angle - (FOV / 2)) || (angle > m->p.angle + (FOV / 2)))
			break;
		if (m->map.map[(int)(yin / m->map.tile)][(int)(xin / m->map.tile)] == '1')
		{
			m->rays[m->ray].x_vert_wall = xin;
			m->rays[m->ray].y_vert_wall = yin;
			return ;
		}
		xin += xstep;
		yin += ystep;
	}
}

void	define_wall_distance(double x, double y, t_mlx *m, double angle)
{
	double	horz_distance;
	double	vert_distance;

	m->rays[m->ray].down = -1;
	if (angle > 0 && angle < M_PI)
		m->rays[m->ray].down = 1;
	m->rays[m->ray].right = -1;
	if (angle < M_PI_2 || angle > 3 * M_PI_2)
		m->rays[m->ray].right = 1;
	vertical_wall(x, y, m, angle);
	horizontal_wall(x, y, m, angle);
		horz_distance = SIZE_MAX;
	if (m->rays[m->ray].x_horz_wall != -1)
		horz_distance = calc_distance(x, y
		, m->rays[m->ray].x_horz_wall, m->rays[m->ray].y_horz_wall);
	vert_distance = SIZE_MAX;
	if (m->rays[m->ray].x_vert_wall != -1)
		vert_distance = calc_distance(x, y
		, m->rays[m->ray].x_vert_wall, m->rays[m->ray].y_vert_wall);	
	m->rays[m->ray].xwall = m->rays[m->ray].x_horz_wall;
	m->rays[m->ray].ywall = m->rays[m->ray].y_horz_wall;
	m->rays[m->ray].wall_distance = horz_distance;
	if (vert_distance < horz_distance)
	{
		m->rays[m->ray].xwall = m->rays[m->ray].x_vert_wall;
		m->rays[m->ray].ywall = m->rays[m->ray].y_vert_wall;
		m->rays[m->ray].wall_distance = vert_distance;
	}
}
