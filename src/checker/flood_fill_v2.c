/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:49:18 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/16 15:51:27 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

static void	f_fill_2(t_map *map, int y, int x);
static void	flf_check_2(t_main *main, int y, int x);
static void	check_invalid_map(t_main *main, int y, int x);

void	flood_fill_2(t_main *main)
{
	main->map->copy_map = ft_map_dup(main->map->map);
	f_fill_2(main->map, main->player_pos->y, main->player_pos->x);
	flf_check_2(main, main->player_pos->y, main->player_pos->x);
	free_copy_map(main->map);
}

static void	f_fill_2(t_map *map, int y, int x)
{
	if (y < 0 || x < 0 || y >= map->map_max_y + 2 || x >= map->map_max_x + 2)
		return ;
	if (map->copy_map[y][x] == 'F' || map->copy_map[y][x] == ' '
		|| map->copy_map[y][x] == '1' || map->copy_map[y][x] == 'B'
		|| ft_strchr("NSWE", map->copy_map[y][x]))
		return ;
	map->copy_map[y][x] = 'F';
	f_fill_2(map, y - 1, x);
	f_fill_2(map, y + 1, x);
	f_fill_2(map, y, x - 1);
	f_fill_2(map, y, x + 1);
}

static void	check_invalid_map(t_main *main, int y, int x)
{
	if (main->map->copy_map[y][x] == '0'
		&& (main->map->copy_map[y - 1][x] == 'B'
		|| main->map->copy_map[y + 1][x] == 'B'
		|| main->map->copy_map[y][x + 1] == 'B'
		|| main->map->copy_map[y][x - 1] == 'B'))
	{
		printf("Error: Invalid map.\n");
		free_copy_map(main->map);
		free_all(main);
		exit(1);
	}
}

static void	flf_check_2(t_main *main, int y, int x)
{
	if (y < 0 || x < 0 || y >= main->map->map_max_y + 2
		|| x >= main->map->map_max_x + 2)
		return ;
	if (main->map->copy_map[y][x] == 'F')
		return ;
	check_invalid_map(main, y, x);
	main->map->copy_map[y][x] = 'F';
	flf_check_2(main, y - 1, x);
	flf_check_2(main, y + 1, x);
	flf_check_2(main, y, x - 1);
	flf_check_2(main, y, x + 1);
}
