/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:16:14 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/26 22:14:54 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_door_color(t_mlx *m, int index, double wall_height, int frame)
{
	double	x_pic;
	double	y_pic;
	int		color;

	y_pic = (index / wall_height) * m->door.frames[frame].ht;
	x_pic = floor(m->rays[m->ray].xwall / m->map.tile) * m->map.tile;
	x_pic  = ((m->rays[m->ray].xwall - x_pic) / m->map.tile) * m->door.frames[frame].wt;
	if (m->rays[m->ray].down == 1)
		x_pic = m->door.frames[frame].wt - x_pic;
	if (m->rays[m->ray].hit == VERTICAL)
	{
		x_pic = floor(m->rays[m->ray].ywall / m->map.tile) * m->map.tile;
	 	x_pic  = ((m->rays[m->ray].ywall - x_pic) / m->map.tile) * m->door.frames[frame].wt;
		if (m->rays[m->ray].right == -1)
			x_pic = m->door.frames[frame].wt - x_pic;
	}
	color = my_mlx_pixel_get(&m->door.frames[frame], x_pic, y_pic);
	return (color);
}

void	*open_door(void *p)
{
	t_mlx	*m;
	double	x;
	double	y;
	
	m = p;
	x = (int)(m->rays[NB_RAYS / 2].xwall) / m->map.tile;
	y = (int)(m->rays[NB_RAYS / 2].ywall) / m->map.tile;
	if (m->rays[NB_RAYS / 2].down == -1 && m->rays[NB_RAYS / 2].hit == HORIZONTAL)
		y--;
	if (m->rays[NB_RAYS / 2].right == -1 && m->rays[NB_RAYS / 2].hit == VERTICAL)
		x--;
	m->map.map[(int)y][(int)x] = 'o';
	while (m->door.frame < 3)
	{
		sleep(1);
		m->door.frame++;
	}
	m->door.frame = 0;
	m->map.map[(int)y][(int)x] = 'd';
	return (0);
}


void	*close_door(void *p)
{
	t_mlx	*m;
	int		length;
	double	x;
	double	y;
	int		size;
	
	m = p;
	size = 0;
	length = m->map.tile;
	x = m->p.x + (cos(m->p.angle) * size);
	y = m->p.y + (sin(m->p.angle) * size);
	while (x >= 0 && x <= WIN_WIDTH && y >= 0 && y <= WIN_HEIGHT &&
		m->map.map[(int)y / length][(int)x / length] != 'd')
	{
		size++;
		x = m->p.x + (cos(m->p.angle) * size);
		y = m->p.y + (sin(m->p.angle) * size);
	}
	while (m->door.frame >= 0)
	{
		sleep(1);
		m->door.frame--;
	}
	if (x >= 0 && x <= WIN_WIDTH && y >= 0 && y <= WIN_HEIGHT)
		m->map.map[(int)y / length][(int)x / length] = 'D';
	return (0);
}

void	door(t_mlx *m)
{
	pthread_t	*sprite;

	sprite = (pthread_t *)malloc(sizeof(pthread_t));
	if (m->rays[NB_RAYS / 2].hit_door)
	{
		// m->door_nb = m->rays[NB_RAYS / 2].hit_door - 1;
		pthread_create(sprite, 0, open_door, m);
		pthread_detach(*sprite);
	}
	else
	{
		pthread_create(sprite, 0, close_door, m);
		pthread_detach(*sprite);
	}
	free(sprite);
}