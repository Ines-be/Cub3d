CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDE = include/
LIB = -L libft/ -lft
NAME = cub3d

SRC = src/parsing.c src/errors.c src/utils.c src/utils2.c src/init.c \
	src/add_text.c src/main.c src/get_color.c

OBJS_BASE = $(SRC:.c=.o)
OBJ_PATH = obj/
OBJS = $(addprefix $(OBJ_PATH),$(OBJS_BASE))
OBJS_BONUS = $(addprefix $(OBJ_PATH), $(OBJS_BASE_BONUS))

all: $(OBJ_PATH) $(NAME)

$(NAME) : $(OBJS)
	make -C libft/
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $(NAME) $(OBJS) $(LIB)

$(OBJ_PATH)%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@ 

$(OBJ_PATH):
	mkdir -p obj/
	mkdir -p obj/src/

clean:
	make fclean -C libft/
	rm -rf $(OBJ_PATH)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
