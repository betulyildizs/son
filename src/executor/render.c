#include "../../lib/cub3d.h"

void	move_forward(t_main *main, const double delta_time)
{
	double			speed;
	int				new_y;
	int				new_x;

	speed = delta_time * MOVE_SPEED;
	new_y = (int)(main->player_pos->y + (main->player_pos->diry * speed));
	new_x = (int)(main->player_pos->x);
	if (main->map->map[new_y][new_x] != '1')
		main->player_pos->y += main->player_pos->diry * speed;
	new_y = (int)(main->player_pos->y);
	new_x = (int)(main->player_pos->x + (main->player_pos->dirx * speed));
	if (main->map->map[new_y][new_x] != '1')
		main->player_pos->x += main->player_pos->dirx * speed;
}

void	move_backward(t_main *main, const double delta_time)
{
	double			speed;
	int				new_y;
	int				new_x;

	speed = delta_time * MOVE_SPEED;
	new_y = (int)(main->player_pos->y - (main->player_pos->diry * speed));
	new_x = (int)(main->player_pos->x);
	if (main->map->map[new_y][new_x] != '1')
		main->player_pos->y -= main->player_pos->diry * speed;
	new_y = (int)(main->player_pos->y);
	new_x = (int)(main->player_pos->x - (main->player_pos->dirx * speed));
	if (main->map->map[new_y][new_x] != '1')
		main->player_pos->x -= main->player_pos->dirx * speed;
}

void	move_right(t_main *main, const double delta_time)
{
	double			speed;
	int				new_y;
	int				new_x;

	speed = delta_time * MOVE_SPEED;
	new_y = (int)(main->player_pos->y);
	new_x = (int)(main->player_pos->x - (main->player_pos->diry * speed));
	if (main->map->map[new_y][new_x] != '1')
		main->player_pos->x -= main->player_pos->diry * speed;
	new_y = (int)(main->player_pos->y + (main->player_pos->dirx * speed));
	new_x = (int)(main->player_pos->x);
	if (main->map->map[new_y][new_x] != '1')
		main->player_pos->y += main->player_pos->dirx * speed;
}

void	move_left(t_main *main, const double delta_time)
{
	double			speed;
	int				new_y;
	int				new_x;

	speed = delta_time * MOVE_SPEED;
	new_y = (int)(main->player_pos->y);
	new_x = (int)(main->player_pos->x + (main->player_pos->diry * speed));
	if (main->map->map[new_y][new_x] != '1')
		main->player_pos->x += main->player_pos->diry * speed;
	new_y = (int)(main->player_pos->y - (main->player_pos->dirx * speed));
	new_x = (int)(main->player_pos->x);
	if (main->map->map[new_y][new_x] != '1')
		main->player_pos->y -= main->player_pos->dirx * speed;
}

void resize_window(t_main *main, int new_width, int new_height) 
{
    mlx_destroy_window(main->mlx.mlx, main->mlx.win);
    main->mlx.win = mlx_new_window(main->mlx.mlx, new_width, new_height, "KANZILETTO CUB3D");
    main->mlx.image.img = mlx_new_image(main->mlx.mlx, new_width, new_height);
    main->mlx.image.addr = mlx_get_data_addr(main->mlx.image.img, &main->mlx.image.bpp,
                                              &main->mlx.image.size_line, &main->mlx.image.endian);
    
    display(main);
}

int	render(void *param)
{
	t_main					*main;
	unsigned long long		current;
	double					delta_time;
	double					angle;

	main = param;
	current = get_timestamp();
	delta_time = (current - main->mlx.last_tick) / 1000.0;
	main->mlx.last_tick = current;
	angle = delta_time * 180 * ROTATION_SPEED * 3.14 / 180.0;
	int new_width = WIDTH;
    int new_height = HEIGHT;
	if (main->mlx.win) {
        int win_width, win_height;
        mlx_get_window_size(main->mlx.mlx, &win_width, &win_height);
        if (win_width != new_width || win_height != new_height) {
            resize_window(main, new_width, new_height);
        }
    }
	if_condition(main, angle, delta_time);
	if (main->keys.esc_pressed)
	{
		free_all(main);
		exit(1);
	}
	display(main);
	return (1);
}
