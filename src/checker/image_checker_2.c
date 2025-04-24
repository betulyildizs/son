/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_checker_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:46:03 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/20 18:03:38 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

char	check_color(t_textures *textures)
{
	int	i;

	i = 0;
	while (textures->c[i])
	{
		if (check_color_value(textures->c[i]) == EXIT_FAILURE)
		{
			printf("Error: Invalid map.\n");
			return (EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (textures->f[i])
	{
		if (check_color_value(textures->f[i]) == EXIT_FAILURE)
		{
			printf("Error: Invalid map.\n");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
