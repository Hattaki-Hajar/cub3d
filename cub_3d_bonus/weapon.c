/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:07:23 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/28 18:45:49 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*gun_animation(void	*p)
{
	t_mlx	*m;

	m = p;
	while (1)
	{
		m->weapon.frame = 0;
		while (m->weapon.frame < m->weapon.nb_frame - 1)
		{
			m->weapon.frame++;
			usleep(200000);
		}
		sleep(2);
	}
}

void	weapon(t_mlx *m)
{
	pthread_t	weapon;

	pthread_create(&weapon, 0, gun_animation, m);
	pthread_detach(weapon);
}
