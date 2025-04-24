/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:54:00 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/18 19:54:25 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	set_dir_values(t_positon *pos, float dir[2], float plane[2])
{
	pos->dirx = dir[0];
	pos->diry = dir[1];
	pos->planex = plane[0];
	pos->planey = plane[1];
}

void	set_north_direction(float dir[2], float plane[2])
{
	dir[0] = 0;
	dir[1] = -1;
	plane[0] = 0.66;
	plane[1] = 0;
}

void	set_south_direction(float dir[2], float plane[2])
{
	dir[0] = 0;
	dir[1] = 1;
	plane[0] = -0.66;
	plane[1] = 0;
}

void	set_east_direction(float dir[2], float plane[2])
{
	dir[0] = 1;
	dir[1] = 0;
	plane[0] = 0;
	plane[1] = 0.66;
}

void	set_west_direction(float dir[2], float plane[2])
{
	dir[0] = -1;
	dir[1] = 0;
	plane[0] = 0;
	plane[1] = -0.66;
}
