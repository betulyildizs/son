#include "../../lib/cub3d.h"

static int  init_mlx_window(t_mlx *mlx)
{
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "KANZILETTO CUB3D");
	if (!mlx->win)
	{
		mlx_destroy_display(mlx->mlx);
		return (1);
	}
	return (0);
}

static int  init_main_image(t_mlx *mlx)
{
	mlx->image.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->image.img)
	{
		mlx_clear_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		return (1);
	}
	mlx->image.addr = mlx_get_data_addr(mlx->image.img, &mlx->image.bpp,
			&mlx->image.size_line, &mlx->image.endian);
	if (!mlx->image.addr)
	{
		mlx_clear_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		return (1);
	}
	return (0);
}

int     init_texture(t_mlx *mlx, void **img, char *path, t_image *texture)
{
	*img = mlx_xpm_file_to_image(mlx->mlx, path,
			&texture->width, &texture->height);
	if (!*img)
	{
		mlx_clear_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		return (1);
	}
	texture->addr = mlx_get_data_addr(*img, &texture->bpp,
			&texture->size_line, &texture->endian);
	return (0);
}

int	close_window(void *param)
{
	t_main	*main;

	main = param;
	free_all(main);
	exit(0);
	return (0);
}

static void	setup_hooks(t_mlx *mlx, t_main *main)
{
	mlx_hook(mlx->win, 2, (1L << 0), key_press, main);
	mlx_hook(mlx->win, 3, (1L << 1), key_release, main);
	mlx_hook(mlx->win, 17, 0, close_window, main);
	mlx_loop_hook(mlx->mlx, render, main);
}

int init_mlx(t_main *main, t_mlx *mlx)
{
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
        return (0);
    
    mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "KANZILETTO CUB3D");
    if (!mlx->win)
    {
        free(mlx->mlx);
        mlx->mlx = NULL;
        return (0);
    }
    
    mlx->image.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
    if (!mlx->image.img)
    {
        mlx_destroy_window(mlx->mlx, mlx->win);
        free(mlx->mlx);
        mlx->mlx = NULL;
        return (0);
    }
    
    mlx->image.addr = mlx_get_data_addr(mlx->image.img, &mlx->image.bpp,
            &mlx->image.size_line, &mlx->image.endian);
    
    // Initialize each texture with proper error handling
    if (init_texture(mlx, &mlx->we_text.img, main->textures->we, &mlx->we_text) ||
        init_texture(mlx, &mlx->ea_text.img, main->textures->ea, &mlx->ea_text) ||
        init_texture(mlx, &mlx->so_text.img, main->textures->so, &mlx->so_text) ||
        init_texture(mlx, &mlx->no_text.img, main->textures->no, &mlx->no_text))
    {
        // Clean up what's been allocated
        clean_mlx(mlx);
        return (0);
    }
    
    setup_hooks(mlx, main);
    
    // Start the mlx loop - note that this is a blocking call and won't return until the window is closed
    mlx_loop(mlx->mlx);
    
    // This will only be reached if mlx_loop returns (not normally expected)
    clean_mlx(mlx);
    return (1);
}