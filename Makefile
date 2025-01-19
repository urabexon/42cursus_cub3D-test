# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 17:33:31 by hurabe            #+#    #+#              #
#    Updated: 2025/01/19 21:25:34 by hurabe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
LIBX_FLAGS	=	-L$(MLX_PATH) -lmlx -lXext -lX11 -lm -O3

SRC_DIR		=	srcs
SRCS = main.c \
	#   check_map.c \
	#   check_player.c \
	#   dda.c \
	#   debug.c \
	#   draw_3d_map.c \
	#   draw_helper.c \
	#   draw_minimap.c \
	#   events.c \
	#   exit.c \
	#   init_map.c \
	#   init_metadata.c \
	#   init_mlx.c \
	#   init.c \
	#   movement.c \
	#   raycast.c \
	#   render.c \
	#   setup.c \
	#   utils.c \
	   gnl/get_next_line.c \
	   gnl/get_next_line_utils.c \
	   libft/ft_atoi.c \
	   libft/ft_bzero.c \
	   libft/ft_calloc.c \
	   libft/ft_isdigit.c \
	   libft/ft_isspace.c \
	   libft/ft_memcpy.c \
	   libft/ft_memset.c \
	   libft/ft_putstr_fd.c \
	   libft/ft_split.c \
	   libft/ft_strchr.c \
	   libft/ft_strcmp.c \
	   libft/ft_strdup.c \
	   libft/ft_strlen.c \
	   libft/ft_substr.c \

# MINILIBX CONFIGURATION
MLX_PATH	=	minilibx-linux/
MLX_NAME	=	libmlx.a
MLX_HEADER	=   $(MLX_PATH)/mlx.h
MLX			=	$(MLX_PATH)$(MLX_NAME)

# OBJECT FILES
OBJ_DIR = objs
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# HEADER FILES
INCS = -I includes -I$(MLX_PATH)
# INCS = -I includes

GREEN = \033[38;5;082;1m
END = \033[0m

.PHONY: all clean fclean re

all: $(MLX) $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Compiling $(NAME)...$(END)"
	@$(CC) $(OBJS) $(CFLAGS) $(LIBX_FLAGS) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/libft
	@mkdir -p $(OBJ_DIR)/gnl

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(MLX_HEADER) | $(OBJ_DIR) 
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# BUILD MINILIBX
$(MLX):
	@git submodule init
	@git submodule update
	$(MAKE) -C $(MLX_PATH)

clean:
	@echo "$(GREEN)Removing object files...$(END)"
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_PATH) clean

fclean: clean
	@echo "$(GREEN)Removeing $(NAME)...$(END)"
	@rm -rf $(NAME)

re : fclean all