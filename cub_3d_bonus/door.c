/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:16:14 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/22 22:30:22 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_door_color(t_mlx *m, int index, double wall_height, int frame)
{
	double	x_pic;
	double	y_pic;
	int		color;

	y_pic = (index / wall_height) * m->door.frame[frame].ht;
	x_pic = floor(m->rays[m->ray].xwall / m->map.tile) * m->map.tile;
	x_pic  = ((m->rays[m->ray].xwall - x_pic) / m->map.tile) * m->door.frame[frame].wt;
	if (m->rays[m->ray].down == 1)
		x_pic = m->door.frame[frame].wt - x_pic;
	if (m->rays[m->ray].hit == VERTICAL)
	{
		x_pic = floor(m->rays[m->ray].ywall / m->map.tile) * m->map.tile;
	 	x_pic  = ((m->rays[m->ray].ywall - x_pic) / m->map.tile) * m->door.frame[frame].wt;
		if (m->rays[m->ray].right == -1)
			x_pic = m->door.frame[frame].wt - x_pic;
	}
	color = my_mlx_pixel_get(&m->door.frame[frame], x_pic, y_pic);
	return (color);
}

void	draw_ray_wall_inter(t_mlx *m, double wall_height, int frame)
{
	int		i;
	int		draw_index;
	int		wall_start;
	int		color;
	
	i = 0;
	draw_index = (WIN_HEIGHT - wall_height) / 2;
	if (draw_index < 0)
		draw_index = 0;
	if (wall_height > WIN_HEIGHT)
		i = (wall_height - WIN_HEIGHT) / 2;
	wall_start = draw_index;
	while (draw_index < WIN_HEIGHT && draw_index - wall_start < wall_height)
	{
		color = find_door_color(m, i, wall_height, frame);
		if (draw_index >= 0 && draw_index <= WIN_HEIGHT
			&& m->ray >= 0 && m->ray <= WIN_WIDTH)
			my_mlx_pixel_put(m, m->ray, draw_index, color);
		i++;
		draw_index++;
	}
	
}

void	draw_wall(t_mlx *m, int frame)
{
	double	wall_height;
	double	projection_distance;

	projection_distance = (WIN_WIDTH / 2) / tan(FOV / 2);
	m->ray = (NB_RAYS / 2);
	// printf("frame %d\n", frame);
	while (m->rays[m->ray].hit_door && m->ray < NB_RAYS)
	{
		wall_height = (m->map.tile / m->rays[m->ray].wall_distance)
			* projection_distance;
		draw_ray_wall_inter(m, wall_height, frame);
		m->ray++;
	}
	m->ray = (NB_RAYS / 2);
	while (m->rays[m->ray].hit_door && m->ray >= 0)
	{
		wall_height = (m->map.tile / m->rays[m->ray].wall_distance)
			* projection_distance;
		draw_ray_wall_inter(m, wall_height, frame);
		m->ray--;
	}
	m->ray = 0;
}

void	*open_door(void *p)
{
	int		frame;
	t_mlx	*m;
	
	m = p;
	frame = 0;
	while (frame < 2)
	{
		draw_wall(m, frame);
		frame++;
		usleep(100000);
	}
	return (0);
}

// void	*close_door(void *p)
// {
// 	int		frame;
// 	t_mlx	*m;
	
// 	m = p;
// 	frame = 1;
// 	while (frame < 2)
// 	{
// 		draw_wall(m, frame);
// 		frame++;
// 	}
// 	return (0);
// }

void	door(t_mlx *m)
{
	double		x;
	double		y;
	int			size;
	int			length;
	pthread_t	*sprite;

	length = m->map.tile;
	x = (int)(m->rays[NB_RAYS / 2].xwall) / length;
	y = (int)(m->rays[NB_RAYS / 2].ywall) / length;
	if (m->rays[NB_RAYS / 2].down == -1 && m->rays[NB_RAYS / 2].hit == HORIZONTAL)
		y--;
	if (m->rays[NB_RAYS / 2].right == -1 && m->rays[NB_RAYS / 2].hit == VERTICAL)
	x--;
	sprite = (pthread_t *)malloc(sizeof(pthread_t));
	if (m->rays[NB_RAYS / 2].hit_door)
	{
		pthread_create(sprite, 0, open_door, m);
		// pthread_join(*sprite, 0);
		m->map.map[(int)y][(int)x] = 'd';
	}
	else
	{
		// pthread_create(sprite, 0, close_door, m);
		size = 0;
		x = m->p.x + (cos(m->p.angle) * size);
		y = m->p.y + (sin(m->p.angle) * size);
		while (x >= 0 && x <= WIN_WIDTH && y >= 0 && y <= WIN_HEIGHT &&
			m->map.map[(int)y / length][(int)x / length] != 'd')
		{
			size++;
			x = m->p.x + (cos(m->p.angle) * size);
			y = m->p.y + (sin(m->p.angle) * size);
		}
		if (x >= 0 && x <= WIN_WIDTH && y >= 0 && y <= WIN_HEIGHT)
			m->map.map[(int)y / length][(int)x / length] = 'D';
	}
}