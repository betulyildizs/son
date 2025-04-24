/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:27:10 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/24 10:49:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

int	has_non_space_or_newline(const char *str)
{
	if (*str == '\0')
		return (0);
	if (*str != ' ' && *str != '\n' && *str != '1')
		return (1);
	return (has_non_space_or_newline(str + 1));
}

static int	process_line(t_textures *textures, char *line)
{
	t_line_parse	p;
	int				result;

	p = (t_line_parse){textures, line, 0};
	skip_whitespaces(p.line, &p.index);
	if (process_texture_lines(&p))
		return (1);
	if (!ft_find_in_str(p.line, p.textures->keys) && !ft_strchr(p.line
			+ p.index, '\n'))
	{
		if (check_textures_done(p.textures))
			return (1);
		else
			return (2);
	}
	return (0);
}

int fill_textures_struct(t_textures *textures, const char *file_name, t_main *main)
{
    int fd;
    char *line;

    fd = open(file_name, O_RDWR);
    if (fd < 0) {
        perror("Error: Couldn't open texture file");
        return -1;  // Return -1 instead of calling exit directly
    }
    
    while (1) {
        line = get_next_line(fd);
        if (line == NULL)
            break; // Handle end of file or error

        // Process the line, and if there is an error, free the textures
        if (process_line(textures, line) == -1) {
            free(line); // Free the line buffer
            // Free any allocated textures here
            free_textures(textures);
            close(fd);
            return -1;
        }

        free(line); // Free the line buffer
    }
    close(fd); // Ensure you close the file descriptor
    return 0; // Success
}
