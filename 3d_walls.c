/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_walls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:52:20 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/08 22:20:10 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// up = red, down = green, right = blue, left = yellow 

int	get_color(t_mlx	*m, int	colomn)
{
	int	color;

	color = 0;
	if (m->rays[colomn].down == -1 && m->rays[colomn].hit == HORIZONTAL)
		color = 0xFFE0E3;
	else if (m->rays[colomn].down == 1 && m->rays[colomn].hit == HORIZONTAL)
		color = 0xF2BDC2;
	else if (m->rays[colomn].right == 1 && m->rays[colomn].hit == VERTICAL)
		color = 0xF2D4D7;
	else if (m->rays[colomn].right == -1 && m->rays[colomn].hit == VERTICAL)
		color = 0xF9CCCA;
	return (color);
}

void	render_walls(t_mlx *m, double wall_height, int colomn)
{
	double	j;
	int		i;
	int		init;
	int		color;

	j = 0;
	init = (WIN_HEIGHT - wall_height) / 2;
	if (!(init >= 0 && init <= WIN_HEIGHT))
		init = 0;
	i = 0;
	color = get_color(m, colomn);
	while(i < init)
	{
		my_mlx_pixel_put(m, colomn ,  i , m->map.sky_color);
		i++;
	}
	while (j < WIN_HEIGHT && j < wall_height)
	{
		if (init >= 0 && init <= WIN_HEIGHT
			&& colomn >= 0 && colomn <= WIN_WIDTH)
			my_mlx_pixel_put(m, colomn, init, color);
		j += 1;
		init++;
	}
	i = init;
	while (i < WIN_HEIGHT)
	{
		my_mlx_pixel_put(m, colomn, i, m->map.floor_color);
		i++;
	}
}

void	draw_walls(t_mlx	*m)
{
	int		i;
	// double		draw;
	double	projection_distance;
	double	wall_height;

	i = 0;
	projection_distance = (WIN_WIDTH / 2) / tan(FOV / 2);
	while (i < NB_RAYS)
	{
		wall_height = (m->map.tile / m->rays[i].wall_distance)
			* projection_distance;
		// draw = 0;
		// while (draw < (wall_height / m->map.tile))
		// {
		// 	// printf("y = %f wall %f\n", draw, wall_height);
		// 	my_mlx_pixel_put(m, i, draw, m->map.sky_color);
		// 	draw += 1;
		// }
		render_walls(m, wall_height, i);
		i++;
	}
}
