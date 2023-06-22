/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:35:44 by hhattaki          #+#    #+#             */
/*   Updated: 2023/06/22 20:40:01 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(int x, int y, t_mlx *t, int color, int size)
{
	int	i;
	int	j;

	i = x;
	while (i < size - 1 + x)
	{
		j = y;
		while (j < size - 1 + y)
		{
			my_mlx_pixel_put(t, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_mlx	*t, double angle, double x, double y)
{
	int	size;
	int	l;
	int	x2;
	int	y2;

	size = 0;
	l = t->map.length;
	x2 = x + (cos(angle) * size);
	y2 = y + (sin(angle) * size);
	calc_wall_distance(t, angle, x, y);
	if (t->ray % 3)
		while (t->map.map[y2 / l][x2 / l] != '1')
		{
			my_mlx_pixel_put(t, x2, y2, 0x99aa99FF);
			size++;
			x2 = x + (cos(angle) * size);
			y2 = y + (sin(angle) * size);
		}
}
