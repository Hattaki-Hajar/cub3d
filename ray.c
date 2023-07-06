/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 20:10:38 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/06 20:11:04 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void reset_rays(t_mlx *m)
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
void	cast_rays(double x, double y, t_mlx *m)
{
	double	ray_angle;

	if (m->p.angle < 0 || m->p.angle > 2 * M_PI)
		m->p.angle = normalize_angle(m->p.angle);
	// printf("player : %f => %f\n\r", m->p.angle, m->p.angle * (180 / (M_PI)));
	// printf("distance: %f\n", m->rays[NB_RAYS - 1].wall_distance);
	ray_angle = m->p.angle - (FOV / 2);
	reset_rays(m);
	while (m->ray < NB_RAYS)
	{
		define_wall_distance(x, y, m, ray_angle);
		draw_ray(m, ray_angle, SCALE_FACTOR * x, SCALE_FACTOR * y);
		m->ray++;
		ray_angle += (FOV / NB_RAYS);
	}
}
