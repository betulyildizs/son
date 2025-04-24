/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:23:22 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/18 19:57:06 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

char	ft_find_in_str(char *line, char *str)
{
	int		i;
	int		j;
	bool	found;

	i = 0;
	j = 0;
	found = false;
	while (line[i] != '\0')
	{
		j = 0;
		found = false;
		while (str[j] != '\0')
		{
			if (line[i] == str[j])
			{
				found = true;
				break ;
			}
			j++;
		}
		if (!found)
			return (false);
		i++;
	}
	return (true);
}

char	skip_whitespaces(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13)))
		(*i)++;
	return (EXIT_SUCCESS);
}

char	check_textures_done(t_textures *textures)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (textures->textures[i] == 0)
			return (EXIT_FAILURE);
		else
			i++;
	}
	if (cf_count_checker(textures))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	check_fill_done(t_textures *textures)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (textures->textures[i] == 1)
			i++;
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
