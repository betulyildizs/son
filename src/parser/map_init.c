/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:27:43 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/18 19:27:46 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

static void	free_map_2(t_map *map, int last_index)
{
	int	i;

	i = 0;
	while (i < last_index)
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
}

static void	init_map_borders(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->map_max_y + 2)
	{
		j = 0;
		while (j < map->map_max_x + 2)
		{
			map->map[i][j] = 'B';
			j++;
		}
		i++;
	}
}

char	init_map(t_map *map)
{
	int	i;
	int	j;

	map->map = ft_calloc((map->map_max_y + 3), sizeof(char *));
	if (!map->map)
		return (EXIT_FAILURE);
	i = 0;
	while (i < map->map_max_y + 2)
	{
		map->map[i] = ft_calloc((map->map_max_x + 3), sizeof(char));
		if (!map->map[i])
		{
			free_map_2(map, i);
			return (EXIT_FAILURE);
		}
		i++;
	}
	init_map_borders(map);
	return (EXIT_SUCCESS);
}
