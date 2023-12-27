NAME = fdf

OBJ_DIR = obj

SRC_DIR = src/

LIBFT_FLAGS = -L./libft -lft

FLAGS = -framework OpenGL -framework AppKit -I./minilibx-mac -L./minilibx-mac -lmlx

X11_FLAGS = -L/usr/X11/lib -lXext -lX11

STANDARD = /

SRCS = 	${SRC_DIR}fdf.c \
		$(SRC_DIR)cleanup.c \
		$(SRC_DIR)draw.c \
		$(SRC_DIR)errors.c \
		$(SRC_DIR)events.c \
		$(SRC_DIR)read.c \

OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)/%.o, $(SRCS))

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes -g

RM = rm -rf

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJS)
	@$(MAKE) -C ./libft --no-print-directory
	@$(MAKE) -C ./minilibx-mac --no-print-directory
	$(CC) $(CFLAGS) $(LIBFT_FLAGS) $(OBJS) $(LIBFT_OBJS) -o $(NAME) $(FLAGS) $(X11_FLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/$(RAY_DIR)
	mkdir -p $(OBJ_DIR)/$(MAP_DIR)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C ./libft --no-print-directory fclean
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re