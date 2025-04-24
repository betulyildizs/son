/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:27:31 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/18 19:45:20 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

bool	check_map_error(t_main *main, char *line, bool *error)
{
	if (check_textures_done(main->textures))
	{
		printf("Error: Invalid map file\n");
		return (true);
	}
	if (has_non_space_or_newline(line))
		*error = true;
	return (false);
}

void	process_map_line(t_main *main, char *line, int *i)
{
	if (ft_strchr(line, '\n'))
	{
		if (main->map->map_max_x < (int)ft_strlen(line) - 1)
			main->map->map_max_x = ft_strlen(line) - 1;
		(*i)++;
	}
}

int	skip_identifiers(int fd, char **line)
{
	char	*trimmed;
	int		ret;

	while (*line)
	{
		trimmed = ft_strtrim(*line, " ");
		ret = (*trimmed == 'F' || *trimmed == 'C' || *trimmed == 'N'
				|| *trimmed == 'S' || *trimmed == 'E' || *trimmed == 'W'
				|| *trimmed == '\n');
		free(trimmed);
		if (!ret)
			break ;
		free(*line);
		*line = get_next_line(fd);
	}
	return (0);
}
