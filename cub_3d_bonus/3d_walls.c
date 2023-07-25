/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_walls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:52:20 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/25 20:57:58 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_color(t_mlx *m, double wall_height, int j, int mode)
{
	double	x_pic;
	double	y_pic;
	int		color;

	y_pic = (j / wall_height) * m->t[mode].ht;
	x_pic = floor(m->rays[m->ray].xwall / m->map.tile) * m->map.tile;
	x_pic  = ((m->rays[m->ray].xwall - x_pic) / m->map.tile) * m->t[mode].wt;
	if (m->rays[m->ray].down == 1)
		x_pic = m->t[mode].wt - x_pic;
	if (m->rays[m->ray].hit == VERTICAL)
	{
		x_pic = floor(m->rays[m->ray].ywall / m->map.tile) * m->map.tile;
	 	x_pic  = ((m->rays[m->ray].ywall - x_pic) / m->map.tile) * m->t[mode].wt;
		if (m->rays[m->ray].right == -1)
			x_pic = m->t[mode].wt - x_pic;
	}
	color = my_mlx_pixel_get(&m->t[mode], x_pic, y_pic);
	return (color);
}

int	choose_texture(t_mlx *m)
{
	if (m->rays[m->ray].hit == HORIZONTAL && m->rays[m->ray].down == -1)
		return (NORTH);
	else if (m->rays[m->ray].hit == HORIZONTAL && m->rays[m->ray].down == 1)
		return (SOUTH);
	else if (m->rays[m->ray].hit == VERTICAL && m->rays[m->ray].right == -1)
		return (WEST);
	else if (m->rays[m->ray].hit == VERTICAL && m->rays[m->ray].right == 1)
		return (EAST);
	return (-1);
}

void	draw_floor_sky(t_mlx *m, int colomn, int height, int mode)
{
	int	i;

	if (height > WIN_HEIGHT)
		return ;
	if (mode == SKY)
	{
		i = 0;
		while (i < height)
		{
			my_mlx_pixel_put(m, colomn, i, m->map.sky_color);
			i++;
		}
	}
	else
	{
		i = height;
		while (i < WIN_HEIGHT)
		{
			my_mlx_pixel_put(m, colomn, i, m->map.floor_color);
			i++;
		}
	}
}

void	render_walls(t_mlx *m, double wall_height)
{
	int		j;
	int		draw_index;
	int		color;
	int		mode;
	int		wall_start;

	j = 0;
	draw_index = (WIN_HEIGHT - wall_height) / 2;
	if (draw_index < 0)
		draw_index = 0;
	if (wall_height > WIN_HEIGHT)
		j = (wall_height - WIN_HEIGHT) / 2;
	draw_floor_sky(m, m->ray, draw_index, SKY);
	wall_start = draw_index;
	while (draw_index < WIN_HEIGHT && draw_index - wall_start < wall_height)
	{
		mode = choose_texture(m);
			color = find_color(m, wall_height, j, mode);
		if (m->rays[m->ray].hit_door == 1)
			color = find_door_color(m, j, wall_height, 0);
		if (m->rays[m->ray].hit_door == 2)
			color = find_door_color(m, j, wall_height, m->door.frame);
		if (draw_index >= 0 && draw_index <= WIN_HEIGHT
			&& m->ray >= 0 && m->ray <= WIN_WIDTH)
			my_mlx_pixel_put(m, m->ray, draw_index, color);
		j++;
		draw_index++;
	}
	draw_floor_sky(m, m->ray, draw_index, FLOOR);
}

void	draw_walls(t_mlx *m)
{
	double	projection_distance;
	double	wall_height;

	m->ray = 0;
	projection_distance = (WIN_WIDTH / 2) / tan(FOV / 2);
	while (m->ray < NB_RAYS)
	{
		wall_height = (m->map.tile / m->rays[m->ray].wall_distance)
			* projection_distance;
		render_walls(m, wall_height);
		m->ray++;
	}
	m->ray = 0;
}
