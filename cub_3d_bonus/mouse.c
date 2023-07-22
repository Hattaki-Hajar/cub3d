/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 22:23:46 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/18 00:48:34 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse(int x, int y, void *p)
{
	t_mlx	*m;

	m = p;
	mlx_mouse_hide();
	if (x != m->mouse.x || y != m->mouse.y)
	{
		if (x < m->mouse.x)
			m->p.turn = -1;
		if (x >= m->mouse.x)
			m->p.turn = 1;
		m->p.angle += m->p.turn * 3 * m->p.rot_speed;
	}
	m->mouse.x = x;
	m->mouse.y = y;
	if (x > WIN_WIDTH || x < 0)
	{
		mlx_mouse_move(m->win_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		m->mouse.x = WIN_WIDTH / 2;
		m->mouse.y = WIN_HEIGHT / 2;
	}
	return (0);
}
