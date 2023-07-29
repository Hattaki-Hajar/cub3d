/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:19:13 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/29 19:14:55 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_keys(t_mlx *m)
{
	m->key.w = 0;
	m->key.s = 0;
	m->key.a = 0;
	m->key.d = 0;
	m->key.left = 0;
	m->key.right = 0;
	m->mouse.x = 0;
	m->mouse.y = 0;
}

void	init_player(t_mlx *m)
{
	m->p.radius = 5;
	m->p.turn = 1;
	m->p.speed = 5;
	m->door.frame = 0;
	m->p.rot_speed = 2 * (M_PI / 180);
}

void	init_weapon_frames(t_mlx *m)
{
	int	i;

	i = 0;
	m->weapon.nb_frame = 5;
	m->weapon.t[0].path = "./textures/moonwand0.xpm";
	m->weapon.t[1].path = "./textures/moonwand1.xpm";
	m->weapon.t[2].path = "./textures/moonwand2.xpm";
	m->weapon.t[3].path = "./textures/moonwand3.xpm";
	m->weapon.t[4].path = "./textures/moonwand5.xpm";
	while (i < m->weapon.nb_frame)
	{
		m->weapon.t[i].xpm_ptr = mlx_xpm_file_to_image(m->mlx_ptr,
				m->weapon.t[i].path, &m->weapon.t[i].wt, &m->weapon.t[i].wt);
		i++;
	}
}

void	init_door_frames(t_mlx *m)
{
	m->door.frames[0].path = "./textures/0.xpm";
	m->door.frames[1].path = "./textures/1.xpm";
	m->door.frames[2].path = "./textures/2.xpm";
	m->door.frames[3].path = "./textures/3.xpm";
	m->door.frames[4].path = "./textures/4.xpm";
	m->door.frames[5].path = "./textures/5.xpm";
	m->door.frames[6].path = "./textures/6.xpm";
	m->door.frames[7].path = "./textures/7.xpm";
	m->door.frames[8].path = "./textures/8.xpm";
	m->door.frames[9].path = "./textures/9.xpm";
	m->door.frames[10].path = "./textures/10.xpm";
	m->door.frames[11].path = "./textures/11.xpm";
}

void	init(t_mlx *m)
{
	init_keys(m);
	init_player(m);
	m->map.tile = 50;
	m->p.x = 2 * m->map.tile + (m->map.tile / 2);
	m->p.y = 2 * m->map.tile + (m->map.tile / 2);
	m->p.angle = 270 * (M_PI / 180);
	m->t[SOUTH].path = "./textures/sailor3.xpm";
	m->t[NORTH].path = "./textures/sailor1.xpm";
	m->t[WEST].path = "./textures/sailor2.xpm";
	m->t[EAST].path = "./textures/sailor0.xpm";
	m->weapon.nb_frame = 7;
	init_weapon_frames(m);
	init_door_frames(m);
	open_textures(m);
}
