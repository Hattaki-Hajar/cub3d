/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:48:13 by hhattaki          #+#    #+#             */
/*   Updated: 2023/06/17 22:54:10 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	// if ((x >= 0 && x <= WIN_WIDTH) || (y >= 0 && y <= WIN_HEIGHT))
	// {
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	// }
}

void	draw_square(int x, int y, t_mlx *t, int color, int size)
{
	for(int i = x; i < size - 1 + x; i++)
	{
		for(int j = y; j < size - 1 + y; j++)
		{
			my_mlx_pixel_put(t, i, j, color);
		}
	}
}
void draw_player(double x, double y, t_mlx *t, int size)
{
	int	i, j;

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
	size = 0;
	while (size < 20)
	{
		my_mlx_pixel_put(t, x + (cos(t->p.angle_R) * size)
			, y + (sin(t->p.angle_R) * size), PURPLE);
		size++;
	}
	size = 0;
	while (size < 20)
	{
		my_mlx_pixel_put(t, 1+ x + (cos(t->p.angle_R) * size)
			, 1 + y + (sin(t->p.angle_R) * size), PURPLE);
		size++;
	}
}

void	fx(void *t)
{
	t_mlx	*m;
	int		l;
	m = t;
	l = m->map.length;
	// printf("%d %d %d\n", m->map.x_elements_nb, m->map.y_elements_nb, l);
	int rest_x = (WIN_WIDTH - (m->map.length * m->map.x_elements_nb)) / 2;
	int rest_y = (WIN_HEIGHT - (m->map.length * m->map.y_elements_nb)) / 2;

	mlx_clear_window(m->mlx_ptr, m->win_ptr);
	m->img_ptr = mlx_new_image(m->mlx_ptr, m->map.length * m->map.x_elements_nb, m->map.length * m->map.y_elements_nb);
	m->addr = mlx_get_data_addr(m->img_ptr, &m->bits_per_pixel, &m->line_length, &m->endian);
	// printf("%d %d\n", m->map.x_elements_nb, m->map.y_elements_nb);
	for (int i = 0; i < m->map.y_elements_nb; i++)
	{
		for (int j = 0; j < m->map.x_elements_nb; j++)
		{
			// printf("%d %d [%c]\n", i, j, m->map.map[i][j]);
			if (m->map.map[i][j] != '1')
				draw_square(j * l, i * l, m, 0xFFFFFF, l);
			else
				draw_square(j * l, i * l, m, 0x808080, l);
		}
	}
	draw_player(m->p.x, m->p.y, m, 14 / 2);
	// printf("%d %d\n", rest_x, rest_y);
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
	m->p.x = 2 * m->map.length + (m->map.length / 2) - 5;
	m->p.y = 2 * m->map.length + (m->map.length / 2) - 5;
	m->p.angle_D = 60;
	m->p.angle_R = m->p.angle_D * (M_PI / 180);
	m->p.radius = 5;
	m->p.turn = 0; 
}

int	main(void)
{
	t_mlx *m = malloc(sizeof(t_mlx));
	char *map[6]= { "111111",
					"100001",
					"10N101",
					"111111" };
	m->map.map = map;
	m->map.x_elements_nb = 6;
	m->map.y_elements_nb = 4;
	// m->map.length = 50;
	// m->p->x = 0;
	init(m);
	m->mlx_ptr = mlx_init();
	m->win_ptr =  mlx_new_window(m->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	mlx_hook(m->win_ptr, 17, 0, ext, 0);
	// mlx_key_hook(m->win_ptr, move_up, m);
	mlx_hook(m->win_ptr, 2, 0, edit_keys, m);
	// printf("here\n");
	mlx_loop_hook(m->mlx_ptr, move, m);
	mlx_hook(m->win_ptr, 3, 0, edit_keys_2, m);
	mlx_loop(m->mlx_ptr);
}
