/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:53:00 by hhattaki          #+#    #+#             */
/*   Updated: 2023/06/22 20:16:48 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keys_down2(int key, t_mlx	*m)
{
	if (key == 124)
	{
		m->p.turn = 1;
		m->key.right = PRESSED;
	}
	else if (key == 123)
	{
		m->p.turn = -1;
		m->key.left = PRESSED;
	}
}

int	keys_down(int key, void	*t)
{
	t_mlx	*m;

	m = t;
	if (key == 53)
		exit (0);
	if (key == 13 || key == 126)
	{
		m->key.w = PRESSED;
		m->p.walk = 1;
	}
	else if (key == 1 || key == 125)
	{
		m->key.s = PRESSED;
		m->p.walk = -1;
	}
	else if (key == 0)
		m->key.a = PRESSED;
	else if (key == 2)
		m->key.d = PRESSED;
	else
		keys_down2(key, m);
	move(m);
	return (0);
}

void	keys_up2(int key, t_mlx *m)
{
	if (key == 124)
	{
		m->key.right = UNPRESSED;
		m->p.turn = 0;
	}
	else if (key == 123)
	{
		m->key.left = UNPRESSED;
		m->p.turn = 0;
	}
}

int	keys_up(int key, void	*t)
{
	t_mlx	*m;

	m = t;
	if (key == 13 || key == 126)
	{
		m->key.w = UNPRESSED;
		m->p.walk = 0;
	}
	else if (key == 1 || key == 125)
	{
		m->key.s = UNPRESSED;
		m->p.walk = 0;
	}
	else if (key == 0)
		m->key.a = UNPRESSED;
	else if (key == 2)
		m->key.d = UNPRESSED;
	else
		keys_up2(key, m);
	return (0);
}
