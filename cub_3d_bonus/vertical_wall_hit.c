/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_wall_hit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:24:46 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/26 22:40:52 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calc_vert_steps(t_mlx *m, double angle, double *xstep, double *ystep)
{
	double	xin;

	*xstep = m->map.tile;
	*ystep = m->map.tile * tan(angle);
	xin = floor(m->p.x / m->map.tile) * m->map.tile;
	if (m->rays[m->ray].right == 1)
		xin += m->map.tile;
	else
		*xstep *= -1;
	if ((m->rays[m->ray].down == -1 && *ystep > 0)
		|| (m->rays[m->ray].down == 1 && *ystep < 0))
		*ystep *= -1;
	return (xin);
}

int	hit_vert_obstacle(t_mlx *m, int i, double yin, double xin)
{
	if (m->map.map[(int)(yin / m->map.tile)][(int)((xin + i) / m->map.tile)]
		== '1')
		return (1);
	if (m->map.map[(int)(yin / m->map.tile)][(int)((xin + i) / m->map.tile)]
		== 'D')
		return (1);
	if (m->map.map[(int)(yin / m->map.tile)][(int)((xin + i) / m->map.tile)]
		== 'o')
		return (1);
	return (0);
}

void	vert_intersection_points(t_mlx *m, double xin, double yin, int i)
{
	m->rays[m->ray].x_vert_wall = xin;
	m->rays[m->ray].y_vert_wall = yin;
	if (m->map.map[(int)(yin / m->map.tile)][(int)((xin + i) / m->map.tile)]
		== '1')
		m->rays[m->ray].vert_hit_door = 0;
	if (m->map.map[(int)(yin / m->map.tile)][(int)((xin + i) / m->map.tile)]
		== 'D')
		m->rays[m->ray].vert_hit_door = 1;
	if (m->map.map[(int)(yin / m->map.tile)][(int)((xin + i) / m->map.tile)]
		== 'o')
		m->rays[m->ray].vert_hit_door = 2;
}

void	vertical_wall_inter(t_mlx *m, double angle)
{
	double	xin;
	double	yin;
	double	ystep;
	double	xstep;
	int		i;

	i = 0;
	if (m->rays[m->ray].right == -1)
		i = -1;
	xin = calc_vert_steps(m, angle, &xstep, &ystep);
	yin = m->p.y + ((xin - m->p.x) * tan(angle));
	if (isnan(yin))
		yin = 0;
	while ((yin >= 0 && yin <= (m->map.tile * m->map.y_elements_nb))
		&& (xin >= 0 && xin <= (m->map.tile * m->map.x_elements_nb)))
	{
		if (hit_vert_obstacle(m, i, yin, xin))
		{
			vert_intersection_points(m, xin, yin, i);
			return ;
		}
		xin += xstep;
		yin += ystep;
	}
}
