/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:28:04 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/26 23:05:18 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	if ((x >= 0 && x <= WIN_WIDTH) || (y >= 0 && y <= WIN_HEIGHT))
	{
		dst = data->addr + (y * data->line_length
				+ x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	my_mlx_pixel_get(t_mlx *m, int x, int y, int mode)
{
	char	*dst;
	int		color;

	color = PURPLE;
	if (x > m->t[mode].wt || x < 0 || y >= m->t[mode].ht || y < 0)
		return (color);
	dst = m->t[mode].addr + (y * m->t[mode].line_length
			+ x * (m->t[mode].bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}
