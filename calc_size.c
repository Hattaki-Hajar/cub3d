/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:00:27 by hhattaki          #+#    #+#             */
/*   Updated: 2023/06/22 18:21:12 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calc_length_y(int elements_nb)
{
	return (WIN_HEIGHT / elements_nb);
}

int	calc_length_x(int elements_nb)
{
	return (WIN_WIDTH / elements_nb);
}

void	calc_wall_distance(t_mlx *t, double angle, double x, double y)
{
	int		size;
	int		l;
	double	x2;
	double	y2;

	size = 0;
	l = t->map.length;
	x2 = x + (cos(angle) * size);
	y2 = y + (sin(angle) * size);
	while (t->map.map[(int)(y2 / l)][(int)(x2 / l)] != '1')
	{
		size++;
		x2 = x + (cos(angle) * size);
		y2 = y + (sin(angle) * size);
	}
	t->rays[t->ray].x = x2;
	t->rays[t->ray].y = y2;
}
