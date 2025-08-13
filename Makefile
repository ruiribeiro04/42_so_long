# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/08 10:23:10 by ruiferna          #+#    #+#              #
#    Updated: 2025/07/22 12:41:21 by ruiferna         ###   ########.fr        #
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
OBJS_DIR = objs

SRCS = $(SRC_DIR)/so_long.c \
       $(SRC_DIR)/player_movement.c \
       $(SRC_DIR)/player_input.c \
       $(SRC_DIR)/map_validation.c \
       $(SRC_DIR)/map_pathfinding.c \
       $(SRC_DIR)/map_parser.c \
       $(SRC_DIR)/game_rendering.c \
       $(SRC_DIR)/game_init.c \
       $(SRC_DIR)/game_cleanup.c \
       $(SRC_DIR)/file_utils.c

ALL_SRCS = $(SRCS)
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(ALL_SRCS:.c=.o)))

LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

MLX_ARCHIVE = minilibx-linux.tgz

RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
RESET=\033[0m

all: $(LIBFT) $(MLX) $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
	@if [ ! -d "$(OBJS_DIR)" ]; then \
		echo "$(YELLOW)Creating objs directory...$(RESET)"; \
		mkdir $(OBJS_DIR); \
	fi

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJS_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR)

$(MLX_DIR):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		if [ ! -f "$(MLX_ARCHIVE)" ]; then \
			echo "$(RED)Error: $(MLX_ARCHIVE) not found in project root!$(RESET)"; \
			echo "$(RED)Please place $(MLX_ARCHIVE) in the same directory as Makefile$(RESET)"; \
			exit 1; \
		fi; \
		echo "$(YELLOW)Extracting MinilibX from $(MLX_ARCHIVE)...$(RESET)"; \
		tar -xzf $(MLX_ARCHIVE) -C $(LIBS_DIR); \
		echo "$(GREEN)MinilibX extracted successfully!$(RESET)"; \
	else \
		echo "$(YELLOW)MinilibX already exists$(RESET)"; \
	fi

$(MLX): $(MLX_DIR)
	@if [ ! -f "$(MLX)" ]; then \
		echo "$(YELLOW)Compiling MinilibX...$(RESET)"; \
		cd $(MLX_DIR) && ./configure; \
		cd $(MLX_DIR) && make -f Makefile.gen libmlx.a 2>/dev/null || make -f makefile.gen libmlx.a 2>/dev/null || echo "$(GREEN)MinilibX library created!$(RESET)"; \
	fi

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@if [ -d "$(OBJS_DIR)" ]; then \
		rm -rf $(OBJS_DIR); \
	fi
	@if [ -f "$(LIBFT)" ]; then \
		make -C $(LIBFT_DIR) clean; \
	fi
	@if [ -d $(MLX_DIR) ] && [ -f "$(MLX)" ]; then \
		make -C $(MLX_DIR) clean; \
	fi

fclean: clean
	@echo "$(RED)Cleaning executables...$(RESET)"
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME); \
	fi
	@if [ -f "$(LIBFT)" ]; then \
		make -C $(LIBFT_DIR) fclean; \
	fi
	@if [ -d $(MLX_DIR) ]; then \
		rm -rf $(MLX_DIR); \
	fi

re: fclean all

.PHONY: all clean fclean re
