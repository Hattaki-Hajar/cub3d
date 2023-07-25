/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:17:46 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/25 21:00:40 by hhattaki         ###   ########.fr       */
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
		m->rays[m->ray].hit_door = m->rays[m->ray].vert_hit_door;
		m->rays[m->ray].hit = VERTICAL;
	}
	else
	{
		m->rays[m->ray].xwall = m->rays[m->ray].x_horz_wall;
		m->rays[m->ray].ywall = m->rays[m->ray].y_horz_wall;
		m->rays[m->ray].wall_distance = horz_distance;
		m->rays[m->ray].hit_door = m->rays[m->ray].horz_hit_door;
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
	// if (m->rays[m->ray].xwall / m->map.tile <= (m->p.x / m->map.tile) + 3
	// 	&& m->rays[m->ray].ywall / m->map.tile <= (m->p.y / m->map.tile) + 3)
	// 	my_mlx_pixel_put(m, m->rays[m->ray].xwall, m->rays[m->ray].ywall, 0xFF007F);
}
