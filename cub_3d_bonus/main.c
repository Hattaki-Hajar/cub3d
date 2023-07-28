/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:48:13 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/28 18:46:59 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	renderer(void *t)
{
	t_mlx	*m;

	m = t;
	mlx_clear_window(m->mlx_ptr, m->win_ptr);
	m->map.map_img = mlx_new_image(m->mlx_ptr, m->map.x_elements_nb
			* m->map.tile,
			m->map.y_elements_nb * m->map.tile);
	m->addr = mlx_get_data_addr(m->map.map_img, &m->bits_per_pixel,
			&m->line_length, &m->endian);
	draw_map(m);
	cast_rays(m);
	m->img_ptr = mlx_new_image(m->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	m->addr = mlx_get_data_addr(m->img_ptr, &m->bits_per_pixel,
			&m->line_length, &m->endian);
	draw_walls(m);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->img_ptr, 0, 0);
	mlx_destroy_image(m->mlx_ptr, m->img_ptr);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->map.map_img,
		0 - (m->p.x - 125), 0 - (m->p.y - 75));
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr,
		m->weapon.t[m->weapon.frame].xpm_ptr, 750, 400);
	mlx_destroy_image(m->mlx_ptr, m->map.map_img);
}

int	main(void)
{
	t_mlx *m = malloc(sizeof(t_mlx));
	m->rays = malloc(NB_RAYS * sizeof(t_ray));
	char **map = malloc(6 * sizeof(char *));
	map[0] = strdup("1111111111111111111111111");
	map[1] = strdup("1010000100000100000100001");
	map[2] = strdup("10N1D10001000000011000001");
	map[3] = strdup("10000000000D0000100000101");
	map[4] = strdup("1000000000000000000000001");
	map[5] = strdup("1111111111111111111111111");
	m->map.map = map;
	m->map.x_elements_nb = 25;
	m->map.y_elements_nb = 6;
	m->map.floor_color = 0xFFFFFF;
	m->map.sky_color = 0x93CAED;
	m->mlx_ptr = mlx_init();
	init(m);
	m->win_ptr =  mlx_new_window(m->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	weapon(m);
	mlx_hook(m->win_ptr, 17, 0, red_cross, 0);
	mlx_hook(m->win_ptr, 2, 0, keys_down, m);
	mlx_hook(m->win_ptr, 6, 0, mouse, m);
	mlx_loop_hook(m->mlx_ptr, move, m);
	mlx_hook(m->win_ptr, 3, 0, keys_up, m);
	mlx_loop(m->mlx_ptr);
}
