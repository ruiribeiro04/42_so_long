# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/08 10:23:10 by ruiferna          #+#    #+#              #
#    Updated: 2025/06/10 20:17:49 by ruiferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

SRC_DIR = src
INC_DIR = includes
LIBS_DIR = libs
LIBFT_DIR = $(LIBS_DIR)/libft
MLX_DIR = $(LIBS_DIR)/minilibx-linux

SRCS = $(SRC_DIR)/so_long.c \
       $(SRC_DIR)/error_handler.c \
       $(SRC_DIR)/game_utils.c \
       $(SRC_DIR)/initialize_game.c \
       $(SRC_DIR)/keyhandler.c \
       $(SRC_DIR)/logic_utils.c \
       $(SRC_DIR)/map_validator_utils.c \
       $(SRC_DIR)/map_validator.c \
       $(SRC_DIR)/move_player.c \
       $(SRC_DIR)/rendering.c

ALL_SRCS = $(SRCS)
OBJS = $(ALL_SRCS:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

LIBFT_URL = --branch complete https://github.com/ruiribeiro04/42_libft
MLX_URL = https://cdn.intra.42.fr/document/document/32345/minilibx-linux.tgz

all: $(LIBS_DIR) $(LIBFT_DIR) $(MLX_DIR) $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(NAME) compiled successfully!"

%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT): $(LIBFT_DIR)
	@echo "Compiling libft..."
	@make -C $(LIBFT_DIR)

$(LIBS_DIR):
	@if [ ! -d "$(LIBS_DIR)" ]; then \
		echo "Creating libs directory..."; \
		mkdir $(LIBS_DIR); \
	fi

$(LIBFT_DIR): $(LIBS_DIR)
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Cloning libft..."; \
		git clone $(LIBFT_URL) $(LIBFT_DIR); \
		echo "Libft cloned successfully!"; \
	else \
		echo "Libft already exists"; \
	fi

$(MLX_DIR): $(LIBS_DIR)
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Downloading and extracting MinilibX..."; \
		wget -q $(MLX_URL) -O $(LIBS_DIR)/minilibx.tgz; \
		tar -xzf $(LIBS_DIR)/minilibx.tgz -C $(LIBS_DIR); \
		rm -f $(LIBS_DIR)/minilibx.tgz; \
		echo "MinilibX downloaded and extracted!"; \
	else \
		echo "MinilibX already exists"; \
	fi

$(MLX): $(MLX_DIR)
	@echo "Compiling MinilibX..."
	@make -C $(MLX_DIR)

clean:
	@echo "$(RED)Cleaning object files..."
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@if [ -d $(LIBFT_DIR) ]; then make -C $(LIBFT_DIR) clean; fi
	@if [ -d $(MLX_DIR) ]; then make -C $(MLX_DIR) clean; fi

fclean: clean
	@echo "$(RED)Cleaning everything...$(RESET)"
	@rm -f $(NAME)
	@rm -rf $(LIBFT_DIR)
	@rm -rf $(MLX_DIR)
	@rm -rf $(LIBS_DIR)

re: fclean all

.PHONY: all clean fclean re