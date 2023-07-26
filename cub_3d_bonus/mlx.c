/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:28:04 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/26 22:48:59 by hhattaki         ###   ########.fr       */
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

int	my_mlx_pixel_get(t_texture *t, int x, int y)
{
	char	*dst;
	int		color;

	color = 0;
	if (x > t->wt || x < 0 || y >= t->ht || y < 0)
		return (color);
	dst = t->addr + (y * t->line_length + x * (t->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}
