/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:42:14 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/24 14:15:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/cub3d.h"

static int handle_textures(t_main *main, char *path)
{
    int fd;

    if (!main->textures)
        return (1);
    fd = fill_textures_struct(main->textures, path, main);
    if (fd == -1)
    {
        fprintf(stderr, "Error: Invalid map.\n");
        free_all(main);
        return (1);
    }
    if (check_image(main->textures) || check_color(main->textures) ||
        is_any_texture_file_empty(main->textures))
    {
        fprintf(stderr, "Error: Texture check failed.\n");
        free_all(main);
        return (1);
    }
    return (fd);
}

static void	av_check(int argc, char *av)
{
	int	fd;
	int	len;

	fd = open(av, O_RDWR);
	if (fd == -1)
	{
		close(fd);
		ft_putstr_fd("Error\nFile can not open.\n", 1);
		exit(1);
	}
	close(fd);
	len = ft_strlen(av);
	if (av[len - 1] != 'b' || av[len - 2] != 'u' || av[len - 3] != 'c' || av[len - 4] != '.')
	{
		ft_putstr_fd("Error\nThe file is not '.cub' extension.\n", 1);
		exit(1);
	}
    special_cont(av);
    check_textures_in_map(av);
}

static int	handle_map(t_main *main, int *fd, char *path)
{
	if (get_map_size(main, fd, path))
	{
		free_all(main);
		main = NULL;
		printf("Error: Invalid map.\n");
		return (1);
	}
	if (fill_map_struct(main, fd, path))
	{
		free_all(main);
		main = NULL;
		return (1);
	}
	flood_fill(main);
	flood_fill_2(main);
	if (!get_player_pos(main))
	{
		printf("Error: Invalid map.\n");
		free_all(main);
		main = NULL;
		exit (1);
	}
	return (0);
}

int main(int argc, char **argv)
{
    t_main  *main;
    int     fd;
    int     exit_code;

    if (argc != 2)
    {
        ft_putstr_fd("Usage: ./cub3D <map_file>\n", 1);
        return (1);
    }
    av_check(argc, argv[1]);
    main = init_all(argv[1]);
    if (!main)
    {
        ft_putstr_fd("Initialization failed\n", 1);
        return (1);
    }
    exit_code = 0;
    fd = handle_textures(main, argv[1]);
    if (fd == 1)
    {
        exit_code = 1;
        return (exit_code);
    }
    else if (handle_map(main, &fd, argv[1]))
    {
        exit_code = 1;
        free_all(main);
        return (exit_code);
    }
    else
    {
        main->mlx.last_tick = 0;
        if (!init_mlx(main, &main->mlx))
        {
            exit_code = 1;
            free_all(main);
            return (exit_code);
        }
    }
    return (exit_code);
}