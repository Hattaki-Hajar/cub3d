/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:48:37 by hhattaki          #+#    #+#             */
/*   Updated: 2023/06/17 18:02:38 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	edit_keys(int key, void	*t)
{
	t_mlx	*m;

	m = t;
	if (key == 53)
		exit (0);
	if (key == 13 || key == 126)
		m->key.w = 1;
	else if (key == 1 || key == 125)
		m->key.s = 1;
	else if (key == 0)
		m->key.a = 1;
	else if (key == 2)
		m->key.d = 1;
	move(m);
	return (0);
}

int	edit_keys_2(int key, void	*t)
{
	t_mlx	*m;

	m = t;
	if (key == 53)
		exit (0);
	if (key == 13 || key == 126)
		m->key.w = 0;
	else if (key == 1 || key == 125)
		m->key.s = 0;
	else if (key == 0)
		m->key.a = 0;
	else if (key == 2)
		m->key.d = 0;
	move(m);
	return (0);
}

int	move(void	*t)
{
	t_mlx	*m;
	int jump_step;
	int speed;

	speed = 10;
	m = t;
	if (m->key.w)
	{
		// if (m->p.y - 10 >= 0)
		jump_step = m->p.y - speed;
		if(jump_step < 0)
			jump_step = 0;
		if (m->map.map[(int)(jump_step / m->map.length)][(int) (m->p.x / m->map.length)] != '1')
			m->p.y -= speed;
		m->key.w = 0;
	}
	if (m->key.s)
	{
		// if (m->p.y + 10 <= WIN_HEIGHT)
		jump_step = m->p.y + speed;
		if(jump_step > m->map.y_elements_nb * m->map.length)
			jump_step = m->map.y_elements_nb * m->map.length;
		if (m->map.map[(int)(jump_step / m->map.length)][(int) (m->p.x / m->map.length)] != '1')
			m->p.y += speed;
		m->key.s = 0;
	}
	if (m->key.a)
	{
		// if (m->p.x - 10 >= 0)
		jump_step = m->p.x - speed;
		if(jump_step < 0)
			jump_step = 0;
		if (m->map.map[(int) (m->p.y / m->map.length)][(int)(jump_step / m->map.length)] != '1')
			m->p.x -= speed;
		m->key.a = 0;
	}
	if (m->key.d)
	{
		// if (m->p.x + 10 <= WIN_WIDTH)
		jump_step = m->p.x + speed;
		if(jump_step > m->map.x_elements_nb * m->map.length)
			jump_step = m->map.x_elements_nb * m->map.length;
		if (m->map.map[(int) (m->p.y / m->map.length)][(int)(jump_step / m->map.length)] != '1')
			m->p.x += speed;
		m->key.d = 0;
	}
	fx(m);
	return (0);
	// left arrow 123 right 124
	// printf("%f %f\n", m->p.x, m->p.y);
}

// void	move_down(t_mlx	m)
// {}
