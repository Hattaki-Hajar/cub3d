/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_hits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:38:11 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/28 21:32:12 by hhattaki         ###   ########.fr       */
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
		if (m->map.map[(int)((yin + i) / m->map.tile)][(int)(xin / m->map.tile)]
		== '1')
		{
			m->rays[m->ray].x_horz_wall = xin;
			m->rays[m->ray].y_horz_wall = yin;
			return ;
		}
		xin += xstep;
		yin += ystep;
	}
}

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
		if (m->map.map[(int)(yin / m->map.tile)][(int)((xin + i) / m->map.tile)]
		== '1')
		{
			m->rays[m->ray].x_vert_wall = xin;
			m->rays[m->ray].y_vert_wall = yin;
			return ;
		}
		xin += xstep;
		yin += ystep;
	}
}
