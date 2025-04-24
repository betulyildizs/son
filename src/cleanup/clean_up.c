/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:07:08 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/24 10:15:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void clean_mlx(t_mlx *mlx)
{
    if (!mlx)
        return;
    if (mlx->mlx)
    {
        // Free images first
        if (mlx->image.img) {
            mlx_destroy_image(mlx->mlx, mlx->image.img);
            mlx->image.img = NULL;
        }
        
        if (mlx->so_text.img) {
            mlx_destroy_image(mlx->mlx, mlx->so_text.img);
            mlx->so_text.img = NULL;
        }
        
        if (mlx->we_text.img) {
            mlx_destroy_image(mlx->mlx, mlx->we_text.img);
            mlx->we_text.img = NULL;
        }
        
        if (mlx->no_text.img) {
            mlx_destroy_image(mlx->mlx, mlx->no_text.img);
            mlx->no_text.img = NULL;
        }
        
        if (mlx->ea_text.img) {
            mlx_destroy_image(mlx->mlx, mlx->ea_text.img);
            mlx->ea_text.img = NULL;
        }
        
        // Then destroy window
        if (mlx->win) {
            mlx_destroy_window(mlx->mlx, mlx->win);
            mlx->win = NULL;
        }
        
        // Finally, clean up MLX itself
        mlx_destroy_display(mlx->mlx);
        free(mlx->mlx);
        mlx->mlx = NULL;
    }
}

void	free_copy_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map || !map->copy_map)
		return ;
	while (map->copy_map[i])
	{
		free(map->copy_map[i]);
		i++;
	}
	free(map->copy_map);
	map->copy_map = NULL;
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	if (map->map)
	{
		while (map->map[i])
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
		map->map = NULL;
	}
	free(map);
}

static void free_texture_array(char **array)
{
    int i;

    if (!array)
        return;
    
    i = 0;
    while (array[i])
    {
        free(array[i]);
        array[i] = NULL;
        i++;
    }
    free(array);
}

void free_textures(t_textures *textures)
{
    if (!textures)
        return;
    
    if (textures->no)
        free(textures->no);
    textures->no = NULL;
    
    if (textures->so)
        free(textures->so);
    textures->so = NULL;
    
    if (textures->we)
        free(textures->we);
    textures->we = NULL;
    
    if (textures->ea)
        free(textures->ea);
    textures->ea = NULL;
    
    if (textures->c)
        free_texture_array(textures->c);
    textures->c = NULL;
    
    if (textures->f)
        free_texture_array(textures->f);
    textures->f = NULL;
    
    if (textures->keys)
        free(textures->keys);
    textures->keys = NULL;
    
    if (textures->textures)
        free(textures->textures);
    textures->textures = NULL;
    
    free(textures);
}

void free_all(t_main *main)
{
    if (!main)
        return;
    
    // Free map structure
    if (main->map)
        free_map(main->map);
    main->map = NULL;
    
    // Free textures structure
    if (main->textures)
        free_textures(main->textures);
    main->textures = NULL;
    
    // Free player position
    if (main->player_pos)
        free(main->player_pos);
    main->player_pos = NULL;
    
    // Clean MLX resources
    clean_mlx(&main->mlx);
    
    // Finally free the main structure itself
    free(main);
}
