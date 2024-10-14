CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDE = cub3d.h
LIB = -L libft/ -lft minilibx-linux/libmlx_Linux.a
MLX = -lXext -lX11
NAME = cub3d
# NAME_BONUS = cub3d_bonus

SRC = src/parsing.c src/errors.c src/utils.c src/utils2.c src/init.c \
	src/add_text.c src/main.c src/get_color.c \
	src/map/map_checking.c \
	src/map/test_characters.c \
	src/mlx/mlx.c \
	src/mlx/handle_keyboard_inputs.c \
	src/utils/utils.c

# SRC_BONUS =

OBJS_BASE = $(SRC:.c=.o)
# OBJS_BASE_BONUS = $(SRC_BONUS:.c=.o)
OBJ_PATH = obj/
OBJS = $(addprefix $(OBJ_PATH),$(OBJS_BASE))
# OBJS_BONUS = $(addprefix $(OBJ_PATH), $(OBJS_BASE_BONUS))

all: $(OBJ_PATH) $(NAME)

$(NAME) : $(OBJS)
	make -C libft/
	make -C mlx/
	$(CC) $(CFLAGS) -I $(INCLUDE) $(MLX) -o $(NAME) $(OBJS) $(LIB)

# $(NAME_BONUS) : $(OBJS_BONUS)
# 	make -C libft/
# 	make -C mlx/
# 	$(CC) $(CFLAGS) -I $(INCLUDE) $(MLX) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIB)

$(OBJ_PATH)%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDE) -I $(MLX) -I $(LIB) -c $< -o $@ 

$(OBJ_PATH):
	mkdir -p obj/
	mkdir -p obj/src/
#	mkdir -p obj/source_bonus/

clean:
	make fclean -C libft/
	rm -rf $(OBJ_PATH)
	rm -f $(OBJS)
#	rm -f $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)
#	rm -f $(NAME_BONUS)

re: fclean all

# bonus:	$(OBJ_PATH) $(NAME_BONUS)

.PHONY: all clean fclean re