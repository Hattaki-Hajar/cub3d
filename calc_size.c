/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:00:27 by hhattaki          #+#    #+#             */
/*   Updated: 2023/06/15 17:06:17 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calc_length_y(int elements_nb)
{
	return (WIN_HEIGHT / elements_nb);
}

int	calc_length_x(int elements_nb)
{
	return (WIN_WIDTH / elements_nb);
}
