/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:16:14 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/10 17:43:18 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_textures(t_mlx *m)
{ //"./textures/poland.xpm"
	m->no.xpm_ptr = mlx_xpm_file_to_image(m->mlx_ptr,m->no.path, &m->no.wt, &m->no.ht);
	// printf(" 2 \n");
	if(m->no.xpm_ptr == 0)
	{	
		printf("textures path : %s , is not found\n", m->no.path);
		exit(1);
	}
	m->no.addr = mlx_get_data_addr(m->no.xpm_ptr, &m->no.bits_per_pixel, &m->no.line_length, &m->no.endian);
	// m->no.xpm_ptr = mlx_xpm_file_to_image(m->mlx_ptr, m->no.path, m->map.tile, m->map.tile);
	// m->no.xpm_ptr = mlx_xpm_file_to_image(m->mlx_ptr, m->no.path, m->map.tile, m->map.tile);
	// m->no.xpm_ptr = mlx_xpm_file_to_image(m->mlx_ptr, m->no.path, m->map.tile, m->map.tile);
}

void	put_texture_to_wall(t_mlx *m, double wall_height, int mode)
{
	int	i, j;
	int	color;

	i = 0;
	while (i < NB_RAYS)
	{
		j = 0;
		while (j <= wall_height && j <= WIN_HEIGHT)
		{
				color = my_mlx_pixel_get(m, i, j, mode);
				printf("color %d\n", color);
				my_mlx_pixel_put(m, i, j, color);
			j++;
		}
		i++;
	}
}
