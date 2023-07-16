/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:17:46 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/14 16:37:56 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	first_hit(t_mlx *m, double vert_distance, double horz_distance)
{
	if (vert_distance < horz_distance)
	{
		m->rays[m->ray].xwall = m->rays[m->ray].x_vert_wall;
		m->rays[m->ray].ywall = m->rays[m->ray].y_vert_wall;
		m->rays[m->ray].wall_distance = vert_distance;
		m->rays[m->ray].hit = VERTICAL;
	}
	else
	{
		m->rays[m->ray].xwall = m->rays[m->ray].x_horz_wall;
		m->rays[m->ray].ywall = m->rays[m->ray].y_horz_wall;
		m->rays[m->ray].wall_distance = horz_distance;
		m->rays[m->ray].hit = HORIZONTAL;
	}
}

void	define_wall_distance(t_mlx *m, double angle)
{
	double	horz_distance;
	double	vert_distance;

	m->rays[m->ray].down = -1;
	m->rays[m->ray].right = -1;
	if (angle > 0 && angle < M_PI)
		m->rays[m->ray].down = 1;
	if (angle < M_PI_2 || angle > 3 * M_PI_2)
		m->rays[m->ray].right = 1;
	vertical_wall_inter(m, angle);
	horizontal_wall_inter(m, angle);
	horz_distance = SIZE_MAX;
	if (m->rays[m->ray].x_horz_wall != -1)
		horz_distance = calc_distance(m->p.x, m->p.y,
				m->rays[m->ray].x_horz_wall, m->rays[m->ray].y_horz_wall);
	vert_distance = SIZE_MAX;
	if (m->rays[m->ray].x_vert_wall != -1)
		vert_distance = calc_distance(m->p.x, m->p.y,
				m->rays[m->ray].x_vert_wall, m->rays[m->ray].y_vert_wall);
	first_hit(m, vert_distance, horz_distance);
}

// void	define_wall_distance(double x, double y, t_mlx *m, double angle)
// {
// 	int		size;
// 	int		l;
// 	double	x2;
// 	double	y2;

// 	size = 0;
// 	l = m->map.tile;
// 	x2 = x + (cos(angle) * size);
// 	y2 = y + (sin(angle) * size);
// 	while (m->map.map[(int)(y2 / l)][(int)(x2 / l)] != '1')
// 	{
// 		size++;
// 		x2 = x + (cos(angle) * size);
// 		y2 = y + (sin(angle) * size);
// 	}
// 	m->rays[m->ray].xwall = x2;
// 	m->rays[m->ray].ywall = y2;
// 	m->rays->down = -1;
// 	if (angle > 0 && angle < M_PI)
// 		m->rays->down = 1;
// 	m->rays->right = -1;
// 	if (angle < 0.5 * M_PI || angle > 1.5 * M_PI)
// 		m->rays->right = 1;
// 	m->rays[m->ray].angle = normalize_angle(angle);
// 	m->rays[m->ray].wall_distance = calc_distance(x, y, x2, y2);
// }
