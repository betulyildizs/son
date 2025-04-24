/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:37:34 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/23 18:36:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void    display(t_main *main);

unsigned long long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	key_press(int keycode, void *param)
{
	t_main	*main;

	main = param;
	if (keycode == KEY_W)
		main->keys.w_pressed = 1;
	else if (keycode == KEY_S)
		main->keys.s_pressed = 1;
	else if (keycode == KEY_A)
		main->keys.a_pressed = 1;
	else if (keycode == KEY_D)
		main->keys.d_pressed = 1;
	else if (keycode == KEY_LEFT)
		main->keys.left_pressed = 1;
	else if (keycode == KEY_RIGHT)
		main->keys.right_pressed = 1;
	else if (keycode == KEY_ESC)
		main->keys.esc_pressed = 1;
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_main	*main;

	main = param;
	if (keycode == KEY_W)
		main->keys.w_pressed = 0;
	else if (keycode == KEY_S)
		main->keys.s_pressed = 0;
	else if (keycode == KEY_A)
		main->keys.a_pressed = 0;
	else if (keycode == KEY_D)
		main->keys.d_pressed = 0;
	else if (keycode == KEY_LEFT)
		main->keys.left_pressed = 0;
	else if (keycode == KEY_RIGHT)
		main->keys.right_pressed = 0;
	else if (keycode == KEY_ESC)
		main->keys.esc_pressed = 0;
	return (0);
}

int	rgbtouint(char **colors)
{
	return (ft_atoi(colors[0]) * 65536 + ft_atoi(colors[1]) * 256 + ft_atoi(colors[2]));
}

t_image	*get_texture(t_mlx *mlx, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->raydir_x > 0)
			return (&mlx->ea_text);
		else
			return (&mlx->we_text);
	}
	else
	{
		if (ray->raydir_y > 0)
			return (&mlx->so_text);
		else
			return (&mlx->no_text);
	}
}
