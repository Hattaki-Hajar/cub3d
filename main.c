/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:48:13 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/06 20:11:10 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	if ((x >= 0 && x <= WIN_WIDTH) || (y >= 0 && y <= WIN_HEIGHT))
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void draw_player(double x, double y, t_mlx *t, int size)
{
	int		i, j;

	i = x - size;
	while (i < x + size)
	{
		j = y - size;
		while (j < y + size)
		{
			my_mlx_pixel_put(t, i, j, PURPLE);
			j++;
		}
		i++;
	}
}

void	fx(void *t)
{
	t_mlx	*m;
	int		l;
	m = t;
	l = m->map.tile * SCALE_FACTOR;
	mlx_clear_window(m->mlx_ptr, m->win_ptr);
	m->map.minimap = mlx_new_image(m->mlx_ptr, l * m->map.x_elements_nb,
				l * m->map.y_elements_nb);
	m->addr = mlx_get_data_addr(m->map.minimap, &m->bits_per_pixel,
			&m->line_length, &m->endian);
	for (int i = 0; i < m->map.y_elements_nb; i++)
	{
		for (int j = 0; j < m->map.x_elements_nb; j++)
		{
			if (m->map.map[i][j] != '1')
				draw_square(j * l, i * l, m, 0xFFFFFF, l);
			else
				draw_square(j * l, i * l, m, 0x808080, l);
		}
	}
	draw_player((m->p.x / m->map.tile) * l, (m->p.y / m->map.tile) * l, m,2);
	cast_rays(m->p.x, m->p.y, m);
	// draw_square(100, 100, m, 0xFFFFFF, 10);
	m->img_ptr = mlx_new_image(m->mlx_ptr, WIN_WIDTH,WIN_HEIGHT);
	m->addr = mlx_get_data_addr(m->img_ptr, &m->bits_per_pixel,
			&m->line_length, &m->endian);
	draw_walls(m);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->img_ptr, 0, 0);
	mlx_destroy_image(m->mlx_ptr, m->img_ptr);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->map.minimap, 10, 10);
	mlx_destroy_image(m->mlx_ptr, m->map.minimap);
}

int ext(void)
{
	exit(0);
}

int	destroy(int key)
{
	if (key == 53)
		exit (0);
	return (0);
}


void	init(t_mlx	*m)
{
	m->key.w = 0;
	m->key.s = 0;
	m->key.a = 0;
	m->key.d = 0;
	m->key.left = 0;
	m->key.right = 0;
	if (calc_length_x(m->map.x_elements_nb) < calc_length_y(m->map.y_elements_nb))
		m->map.tile = calc_length_x(m->map.x_elements_nb);
	else
		m->map.tile = calc_length_y(m->map.y_elements_nb);
	m->p.x = 2 * m->map.tile + (m->map.tile / 2);
	m->p.y = 2 * m->map.tile + (m->map.tile / 2);
	m->p.angle = normalize_angle(270 * (M_PI / 180));
	m->p.radius = 5;
	m->p.turn = 0;
	m->p.turn = 1;
	m->p.rot_speed = 2 * (M_PI / 180);
}

int	main(void)
{
	t_mlx *m = malloc(sizeof(t_mlx));
	m->rays = malloc(NB_RAYS * sizeof(t_ray));
	char *map[10]= { "1111111111",
					 "1010001101",
					 "10N1000001",
					 "1000011001",
					 "1000000001",
					 "1111111111"};
	m->map.map = map;
	m->map.x_elements_nb = 10;
	m->map.y_elements_nb = 6;
	init(m);
	m->mlx_ptr = mlx_init();
	m->win_ptr =  mlx_new_window(m->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	mlx_hook(m->win_ptr, 17, 0, ext, 0);
	mlx_hook(m->win_ptr, 2, 0, keys_down, m);
	mlx_loop_hook(m->mlx_ptr, move, m);
	mlx_hook(m->win_ptr, 3, 0, keys_up, m);
	mlx_loop(m->mlx_ptr);
}
