/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:28:04 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/09 22:54:55 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

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

int my_mlx_pixel_get(t_mlx *m, int x, int y, int mode)
{
	char	*dst;
	int		color;

	color = 0;
	if (mode == NORTH)
	{
		dst = m->no.addr + (y * m->no.line_length
				+ x * (m->no.bits_per_pixel / 8));
		color = *(unsigned int *)dst;
	}
	else if (mode == SOUTH)
	{
		dst = m->so.addr + (y * m->so.line_length
				+ x * (m->so.bits_per_pixel / 8));
		color = *(unsigned int *)dst;
	}
	else if (mode == EAST)
	{
		dst = m->ea.addr + (y * m->ea.line_length
				+ x * (m->ea.bits_per_pixel / 8));
		color = *(unsigned int *)dst;
	}
	else
	{
		dst = m->we.addr + (y * m->we.line_length
				+ x * (m->we.bits_per_pixel / 8));
		color = *(unsigned int *)dst;
	}
	return (color);
}
