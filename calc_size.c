/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:00:27 by hhattaki          #+#    #+#             */
/*   Updated: 2023/06/24 20:13:18 by hhattaki         ###   ########.fr       */
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

double	normalize_angle(double	angle)
{
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

double	calc_distance(double x, double y, double xfinal, double yfinal)
{
	double	distance;

	if (x < 0 || y < 0 || xfinal < 0 || yfinal < 0)
		return (-1);
	distance = sqrt((xfinal - x) * (xfinal - x)) +((yfinal - y) * (yfinal - y));
	return (distance);
}

// void	calc_wall_distance(t_mlx *t, double angle, double x, double y)
// {
// 	int		size;
// 	int		l;
// 	double	x2;
// 	double	y2;

// 	size = 0;
// 	l = t->map.length;
// 	x2 = x + (cos(angle) * size);
// 	y2 = y + (sin(angle) * size);
// 	while (t->map.map[(int)(y2 / l)][(int)(x2 / l)] != '1')
// 	{
// 		size++;
// 		x2 = x + (cos(angle) * size);
// 		y2 = y + (sin(angle) * size);
// 	}
// 	t->rays[t->ray].x = x2;
// 	t->rays[t->ray].y = y2;
// 	t->rays->down = -1;
// 	if (angle > 0 && angle < M_PI)
// 		t->rays->down = 1;
// 	t->rays->right = -1;
// 	if (angle < 0.5 * M_PI || angle > 1.5 * M_PI)
// 		t->rays->right = 1;
// 	t->rays[t->ray].angle = normalize_angle(angle);
// }
