/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:48:13 by hhattaki          #+#    #+#             */
/*   Updated: 2023/06/22 20:31:47 by hhattaki         ###   ########.fr       */
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
	double	angle;

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
	angle = t->p.angle - (FOV / 2);
	t->ray = 0;
	while (t->ray < NB_RAYS)
	{
		draw_line(t, angle, x, y);
		angle += FOV / NB_RAYS;
		t->ray++;
	}
}

void	fx(void *t)
{
	t_mlx	*m;
	int		l;
	m = t;
	l = m->map.length;
	int rest_x = (WIN_WIDTH - (m->map.length * m->map.x_elements_nb)) / 2;
	int rest_y = (WIN_HEIGHT - (m->map.length * m->map.y_elements_nb)) / 2;
	mlx_clear_window(m->mlx_ptr, m->win_ptr);
	m->img_ptr = mlx_new_image(m->mlx_ptr, m->map.length * m->map.x_elements_nb, m->map.length * m->map.y_elements_nb);
	m->addr = mlx_get_data_addr(m->img_ptr, &m->bits_per_pixel, &m->line_length, &m->endian);
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
	draw_player(m->p.x, m->p.y, m, 14 / 2);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->img_ptr, rest_x, rest_y);
	mlx_destroy_image(m->mlx_ptr, m->img_ptr);
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
		m->map.length = calc_length_x(m->map.x_elements_nb);
	else
		m->map.length = calc_length_y(m->map.y_elements_nb);
	m->p.x = 2 * m->map.length + (m->map.length / 2) - (double)(10 / 3);
	m->p.y = 2 * m->map.length + (m->map.length / 2) - (double)(10 / 3);
	m->p.angle = 270 * (M_PI / 180);
	m->p.radius = 5;
	m->p.turn = 0;
	m->p.turn = 1;
	m->p.rot_speed = 3 * (M_PI / 180);
}

int	main(void)
{
	t_mlx *m = malloc(sizeof(t_mlx));
	m->rays = malloc(NB_RAYS * sizeof(t_ray));
	char *map[6]= { "111111",
					"101001",
					"10N101",
					"111111" };
	m->map.map = map;
	m->map.x_elements_nb = 6;
	m->map.y_elements_nb = 4;
	init(m);
	m->mlx_ptr = mlx_init();
	m->win_ptr =  mlx_new_window(m->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	mlx_hook(m->win_ptr, 17, 0, ext, 0);
	mlx_hook(m->win_ptr, 2, 0, keys_down, m);
	mlx_loop_hook(m->mlx_ptr, move, m);
	mlx_hook(m->win_ptr, 3, 0, keys_up, m);
	mlx_loop(m->mlx_ptr);
}
