

#include "cub3d.h"

void	render_walls(t_mlx *m, double wall_height, int colomn)
{
	double	j;
	int	init;

	j = 0;
	init = (WIN_HEIGHT - wall_height) / 2;
	if (!(init >= 0 && init <= WIN_HEIGHT))
		init = 0;
	while (j < WIN_HEIGHT && j < wall_height)
	{
		if (init >= 0 && init <= WIN_HEIGHT && colomn >= 0 && colomn <= WIN_WIDTH)
			my_mlx_pixel_put(m, colomn, init, 0x30FFFFFF);
		j+=1;
		init++;
	}
}

void	draw_walls(t_mlx	*m)
{
	int		i;
	double	projection_distance;
	double	wall_height;

	i = 0;
	projection_distance = (WIN_WIDTH / 2) / tan(FOV / 2);
	while (i < NB_RAYS)
	{
		wall_height = (m->map.tile / m->rays[i].wall_distance) * projection_distance;
		render_walls(m, wall_height, i);
		i++;
	}
}
