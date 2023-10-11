# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 18:42:13 by abied-ch          #+#    #+#              #
#    Updated: 2023/10/11 21:10:29 by abied-ch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

OBJ_DIR = obj

SRC_DIR = src

SRCS = 	${SRC_DIR}/read.c \
		${SRC_DIR}/draw.c \
		${SRC_DIR}/fdf.c \
		${SRC_DIR}/events.c \
				
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes -g

LDFLAGS = -Lminilibx-linux -L ./libft -lmlx -lXext -lX11 -lm -lft

RM = rm -rf

.SILENT:

all: $(OBJ_DIR) $(NAME) 

$(NAME): $(OBJS) $(LIBFT_OBJS)
	printf "Compiling libft..."
	$(MAKE) -C ./libft --no-print-directory
	printf "\rCompiling fdf.."
	sleep 0.5
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_OBJS) -o $(NAME) $(LDFLAGS)
	printf "\rCompiling completed.\n"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: libft/src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C ./libft --no-print-directory fclean
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
