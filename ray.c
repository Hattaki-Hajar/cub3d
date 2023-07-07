/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 20:10:38 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/07 19:03:47 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	reset_rays(t_mlx *m)
{
	m->ray = -1;
	while (++m->ray < NB_RAYS)
	{
		m->rays[m->ray].x_horz_wall = -1;
		m->rays[m->ray].y_horz_wall = -1;
		m->rays[m->ray].x_vert_wall = -1;
		m->rays[m->ray].y_vert_wall = -1;
	}
	m->ray = 0;
}

void	cast_rays(t_mlx *m)
{
	double	ray_angle;

	if (m->p.angle < 0 || m->p.angle > 2 * M_PI)
		m->p.angle = normalize_angle(m->p.angle);
	ray_angle = m->p.angle - (FOV / 2);
	reset_rays(m);
	// draw_ray(m, m->p.angle, SCALE_FACTOR * m->p.x, SCALE_FACTOR * m->p.y);
	while (m->ray < NB_RAYS)
	{
		ray_angle = normalize_angle(ray_angle);
		define_wall_distance(m, ray_angle);
		m->rays[m->ray].wall_distance *= cos(ray_angle - m->p.angle);
		// draw_ray(m, ray_angle, SCALE_FACTOR * m->p.x, SCALE_FACTOR * m->p.y);
		m->ray++;
		ray_angle += (FOV / NB_RAYS);
	}
}
