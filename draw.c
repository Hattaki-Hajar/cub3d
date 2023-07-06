/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:35:44 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/06 18:39:23 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(int x, int y, t_mlx *m, int color, int size)
{
	int	i;
	int	j;

	i = x;
	while (i < size - 1 + x)
	{
		j = y;
		while (j < size - 1 + y)
		{
			my_mlx_pixel_put(m, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_mlx	*m, double angle, double x, double y)
{
	int	size;
	double	x2;
	double	y2;

	size = 0;
	x2 = x + (cos(angle) * size);
	y2 = y + (sin(angle) * size);
	while (y2 >= 0 && y2 <= m->rays->ywall && x2 >= 0 && x2 <= m->rays->xwall)
	{
		my_mlx_pixel_put(m, x2, y2, 0x44aa99FF);
		size++;
		x2 = x + (cos(m->rays->angle) * size);
		y2 = y + (sin(m->rays->angle) * size);
	}
}



void	draw_ray(t_mlx	*m, double angle, double x, double y)
{
	int	size;
	int	l;
	int	x2;
	int	y2;

	size = 0;
	l = m->map.tile * SCALE_FACTOR;
	x2 = x + cos(angle);
	y2 = y + sin(angle);
	while (m->map.map[y2 / l][x2 / l] != '1')
	{
		my_mlx_pixel_put(m, x2, y2, 0x99aa99FF);
		size++;
		x2 = x + (cos(angle) * size);
		y2 = y + (sin(angle) * size);
	}
}
