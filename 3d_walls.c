/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_walls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:52:20 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/10 18:39:36 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	get_color(t_mlx	*m, int colomn)
// {
// 	int	color;

// 	color = 0;
// 	if (m->rays[colomn].down == -1 && m->rays[colomn].hit == HORIZONTAL)
// 		color = my_mlx_pixel_get(m, );
// 	else if (m->rays[colomn].down == 1 && m->rays[colomn].hit == HORIZONTAL)
// 		color = 0xF2BDC2;
// 	else if (m->rays[colomn].right == 1 && m->rays[colomn].hit == VERTICAL)
// 		color = 0xF2D4D7;
// 	else if (m->rays[colomn].right == -1 && m->rays[colomn].hit == VERTICAL)
// 		color = 0xF9CCCA;
// 	return (color);
// }

// int	return_color()
// {
	
// }

void	draw_floor_sky(t_mlx *m, int colomn, int height, int mode)
{
	int	i;

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

void	render_walls(t_mlx *m, double wall_height, int colomn)
{
	double	j;
	int		init;
	int		color;
	int		y_pic;
	int		x_pic;

	j = 0;
	if (wall_height > WIN_HEIGHT)
		wall_height = WIN_HEIGHT;
	init = (WIN_HEIGHT - wall_height) / 2;
	if (!(init >= 0 && init <= WIN_HEIGHT))
		init = 0;
	draw_floor_sky(m, colomn, init, SKY);
	while (j < WIN_HEIGHT && j < wall_height)
	{
		y_pic = (j / wall_height) * m->no.ht;
		x_pic = floor(m->rays[colomn].xwall / m->map.tile) * m->map.tile;
		x_pic  = ((m->rays[colomn].xwall - x_pic) / m->map.tile) * m->no.wt;
		if (m->rays[colomn].hit == VERTICAL)
		{
			x_pic = (j / wall_height) * m->no.wt;
			y_pic = floor(m->rays[colomn].ywall / m->map.tile) * m->map.tile;
			y_pic  = ((m->rays[colomn].ywall - y_pic) / m->map.tile) * m->no.ht;
		}
		color = my_mlx_pixel_get(m, x_pic, y_pic, NORTH);
		if (init >= 0 && init <= WIN_HEIGHT
			&& colomn >= 0 && colomn <= WIN_WIDTH)
			my_mlx_pixel_put(m, colomn, init, color);
		j += 1;
		init++;
	}
	draw_floor_sky(m, colomn, init, FLOOR);
}

void	draw_walls(t_mlx	*m)
{
	int		i;
	double	projection_distance;
	double	wall_height;

	i = 0;
	projection_distance = (WIN_WIDTH / 2) / tan(FOV / 2);
	while (i < NB_RAYS)
	{
		wall_height = (m->map.tile / m->rays[i].wall_distance)
			* projection_distance;
		render_walls(m, wall_height, i);
		i++;
	}
}
