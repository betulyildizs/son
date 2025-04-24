NAME = cub3D
CC = cc -g
CFLAGS = -I./lib/libft -I/usr/include -I./lib/minilibx -I2 -I./gnl #-fsanitize=address -g
MLXFLAGS = -L./lib/minilibx -lmlx -L/usr/lib -lXext -lX11 -lm -lz
LIBFT_DIR = ./lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = main.c src/parser/fill_struct.c src/parser/init.c src/utils/parser_utils.c \
	src/utils/parser_utils2.c src/checker/flood_fill_v1.c src/checker/image_checker.c \
	src/cleanup/clean_up.c src/checker/flood_fill_v2.c src/checker/flood_fill_v1_2.c \
	$(LIBFT_SRCS) src/executor/mlx.c src/parser/player.c src/checker/image_checker_2.c \
	src/parser/map_init.c src/parser/map_utils.c src/parser/texture_handlers.c \
	src/parser/texture_processing.c src/parser/player_dir.c src/executor/render.c \
	src/executor/render_rotate.c src/executor/display.c src/executor/ray.c \
	src/executor/init_mlx.c lib/gnl/get_next_line.c lib/gnl/get_next_line_utils.c \
	src/checker/special_cont.c src/checker/special_texture_cont.c \

OBJS = $(SRCS:.c=.o)

MLX_DIR = lib/minilibx
MLX = $(MLX_DIR)/libmlx.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(MLXFLAGS) -o $(NAME)

$(MLX):
	make -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)
	make -C $(MLX_DIR) clean

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f $(MLX_DIR)/libmlx.a

re: fclean all

.PHONY: all clean fclean re
