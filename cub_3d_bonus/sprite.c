/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:07:23 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/22 15:34:37 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	find_door_color(t_mlx *m, double wall_height, int j)
// {
// 	// int	i = 0;
// 	double	x_pic;
// 	double	y_pic;
// 	int		color;

// 	y_pic = (j / wall_height) * m->door.frame[0].ht;
// 	x_pic = floor(m->rays[m->ray].xwall / m->map.tile) * m->map.tile;
// 	x_pic  = ((m->rays[m->ray].xwall - x_pic) / m->map.tile) * m->door.frame[0].wt;
// 	if (m->rays[m->ray].down == 1)
// 		x_pic = m->door.frame[0].wt - x_pic;
// 	if (m->rays[m->ray].hit == VERTICAL)
// 	{
// 		x_pic = floor(m->rays[m->ray].ywall / m->map.tile) * m->map.tile;
// 	 	x_pic  = ((m->rays[m->ray].ywall - x_pic) / m->map.tile) * m->door.frame[0].wt;
// 		if (m->rays[m->ray].right == -1)
// 			x_pic = m->door.frame[0].wt - x_pic;
// 	}
// 	color = my_mlx_pixel_get(&m->door.frame[0], x_pic, y_pic);
// 	return (color);
// }
