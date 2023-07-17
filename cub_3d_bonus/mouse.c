/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 22:23:46 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/16 22:25:23 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse(int x, int y, void *p)
{
	t_mlx	*m;

	m = p;
	if (x != m->mouse.x || y != m->mouse.y)
	{
		if (x < m->mouse.x)
			m->p.turn = -1;
		if (x >= m->mouse.x)
			m->p.turn = 1;
		m->p.angle += m->p.turn * m->p.rot_speed;
	}
	m->mouse.x = x;
	m->mouse.y = y;
	return (0);
}
