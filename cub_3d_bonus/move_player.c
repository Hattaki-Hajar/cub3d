/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:48:37 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/26 22:49:57 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	up(t_mlx *m)
{
	double	jump_x;
	double	jump_y;
	int		l;

	l = m->map.tile;
	jump_y = m->p.y + sin(m->p.angle) * m->p.speed;
	jump_x = m->p.x + cos(m->p.angle) * m->p.speed;
	if (m->map.map[(int)(m->p.y / l)][(int)(jump_x / l)] != '1'
		&& m->map.map[(int)(jump_y / l)][(int)(m->p.x / l)] != '1'
		&& m->map.map[(int)(jump_y / l)][(int)(jump_x / l)] != '1'
		&& m->map.map[(int)(m->p.y / l)][(int)(jump_x / l)] != 'D'
		&& m->map.map[(int)(jump_y / l)][(int)(m->p.x / l)] != 'D'
		&& m->map.map[(int)(jump_y / l)][(int)(jump_x / l)] != 'D')
	{
		m->p.y = jump_y;
		m->p.x = jump_x;
	}
}

void	down(t_mlx *m)
{
	double	jump_x;
	double	jump_y;
	int		l;

	l = m->map.tile;
	jump_y = m->p.y - sin(m->p.angle) * m->p.speed;
	jump_x = m->p.x - cos(m->p.angle) * m->p.speed;
	if (m->map.map[(int)(m->p.y / l)][(int)(jump_x / l)] != '1'
		&& m->map.map[(int)(jump_y / l)][(int)(m->p.x / l)] != '1'
		&& m->map.map[(int)(jump_y / l)][(int)(jump_x / l)] != '1'
		&& m->map.map[(int)(m->p.y / l)][(int)(jump_x / l)] != 'D'
		&& m->map.map[(int)(jump_y / l)][(int)(m->p.x / l)] != 'D'
		&& m->map.map[(int)(jump_y / l)][(int)(jump_x / l)] != 'D')
	{
		m->p.y = jump_y;
		m->p.x = jump_x;
	}
}

void	right(t_mlx	*m)
{
	double	jump_x;
	double	jump_y;
	int		l;

	l = m->map.tile;
	jump_y = m->p.y + sin(m->p.angle + (M_PI / 2)) * m->p.speed;
	jump_x = m->p.x + cos(m->p.angle + (M_PI / 2)) * m->p.speed;
	if (m->map.map[(int)(m->p.y / l)][(int)(jump_x / l)] != '1'
		&& m->map.map[(int)(jump_y / l)][(int)(m->p.x / l)] != '1'
		&& m->map.map[(int)(jump_y / l)][(int)(jump_x / l)] != '1'
		&& m->map.map[(int)(m->p.y / l)][(int)(jump_x / l)] != 'D'
		&& m->map.map[(int)(jump_y / l)][(int)(m->p.x / l)] != 'D'
		&& m->map.map[(int)(jump_y / l)][(int)(jump_x / l)] != 'D')
	{
		m->p.y = jump_y;
		m->p.x = jump_x;
	}
}

void	left(t_mlx *m)
{
	double	jump_x;
	double	jump_y;
	int		l;

	l = m->map.tile;
	jump_y = m->p.y - sin(m->p.angle + (M_PI / 2)) * m->p.speed;
	jump_x = m->p.x - cos(m->p.angle + (M_PI / 2)) * m->p.speed;
	if (m->map.map[(int)(m->p.y / l)][(int)(jump_x / l)] != '1'
		&& m->map.map[(int)(jump_y / l)][(int)(m->p.x / l)] != '1'
		&& m->map.map[(int)(jump_y / l)][(int)(jump_x / l)] != '1'
		&& m->map.map[(int)(m->p.y / l)][(int)(jump_x / l)] != 'D'
		&& m->map.map[(int)(jump_y / l)][(int)(m->p.x / l)] != 'D'
		&& m->map.map[(int)(jump_y / l)][(int)(jump_x / l)] != 'D')
	{
		m->p.y = jump_y;
		m->p.x = jump_x;
	}
}

int	move(void	*t)
{
	t_mlx	*m;

	m = t;
	if (m->key.w == PRESSED)
		up(m);
	if (m->key.s == PRESSED)
		down(m);
	if (m->key.a == PRESSED)
		left(m);
	if (m->key.d == PRESSED)
		right(m);
	if (m->key.left == PRESSED || m->key.right == PRESSED)
		m->p.angle += m->p.turn * m->p.rot_speed;
	renderer(m);
	return (0);
}
