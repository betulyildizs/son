/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_v1_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:02:22 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/16 16:02:51 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	player_pos(t_main *main)
{
	int	i;
	int	j;

	i = -1;
	main->player_pos->count = 0;
	while (main->map->map[++i])
	{
		j = -1;
		while (main->map->map[i][++j])
		{
			if (ft_strchr("NSEW", main->map->map[i][j]))
			{
				main->player_pos->x = j;
				main->player_pos->y = i;
				main->player_pos->count++;
			}
		}
	}
}

char	**ft_map_dup(char **src)
{
	char	**dest;
	int		i;

	i = 0;
	while (src[i])
		i++;
	dest = (char **)malloc(sizeof(char *) * (i + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (src[++i])
	{
		dest[i] = (char *)malloc(sizeof(char) * (ft_strlen(src[i]) + 1));
		if (!dest[i])
			return (NULL);
		copy_row(dest[i], src[i]);
	}
	dest[i] = NULL;
	return (dest);
}
