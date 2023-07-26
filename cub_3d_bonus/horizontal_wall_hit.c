/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_wall_hit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:38:11 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/26 22:40:45 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calc_horz_steps(t_mlx *m, double angle, double *xstep, double *ystep)
{
	double	yin;

	*ystep = m->map.tile;
	*xstep = m->map.tile / tan(angle);
	yin = floor(m->p.y / m->map.tile) * m->map.tile;
	if (m->rays[m->ray].down == 1)
		yin += m->map.tile;
	else
		*ystep *= -1;
	if ((m->rays[m->ray].right == -1 && *xstep > 0)
		|| (m->rays[m->ray].right == 1 && *xstep < 0))
		*xstep *= -1;
	return (yin);
}

int	hit_horz_obstacle(t_mlx *m, int i, double yin, double xin)
{
	if (m->map.map[(int)((yin + i) / m->map.tile)][(int)(xin / m->map.tile)]
		== '1')
		return (1);
	if (m->map.map[(int)((yin + i) / m->map.tile)][(int)(xin / m->map.tile)]
		== 'D')
		return (1);
	if (m->map.map[(int)((yin + i) / m->map.tile)][(int)(xin / m->map.tile)]
		== 'o')
		return (1);
	return (0);
}

void	horz_intersection_points(t_mlx *m, double xin, double yin, int i)
{
	m->rays[m->ray].x_horz_wall = xin;
	m->rays[m->ray].y_horz_wall = yin;
	if (m->map.map[(int)((yin + i) / m->map.tile)][(int)(xin / m->map.tile)]
		== '1')
		m->rays[m->ray].horz_hit_door = 0;
	if (m->map.map[(int)((yin + i) / m->map.tile)][(int)(xin / m->map.tile)]
		== 'D')
		m->rays[m->ray].horz_hit_door = 1;
	if (m->map.map[(int)((yin + i) / m->map.tile)][(int)(xin / m->map.tile)]
		== 'o')
		m->rays[m->ray].horz_hit_door = 2;
}

void	horizontal_wall_inter(t_mlx *m, double angle)
{
	double	xin;
	double	yin;
	double	ystep;
	double	xstep;
	int		i;

	i = 0;
	if (m->rays[m->ray].down == -1)
		i = -1;
	yin = calc_horz_steps(m, angle, &xstep, &ystep);
	xin = m->p.x + ((yin - m->p.y) / tan(angle));
	if (isnan(xin))
		xin = 0;
	while ((yin >= 0 && yin <= (m->map.tile * m->map.y_elements_nb))
		&& (xin >= 0 && xin <= (m->map.tile * m->map.x_elements_nb)))
	{
		if (hit_horz_obstacle(m, i, yin, xin))
		{
			horz_intersection_points(m, xin, yin, i);
			return ;
		}
		xin += xstep;
		yin += ystep;
	}
}
