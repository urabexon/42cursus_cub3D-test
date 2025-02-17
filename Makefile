# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 17:33:31 by hurabe            #+#    #+#              #
#    Updated: 2025/02/17 10:43:53 by kitaoryoma       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
LIBX_FLAGS	=	-L$(MLX_PATH) -lmlx -lXext -lX11 -lm -O3

SRC_DIR		=	srcs
SRCS 		=	main.c \
				validate.c \
				init.c \
				setup.c \
				init_metadata.c \
				init_map.c \
				check_map.c \
				check_player.c \
				exit.c \
				utils.c \
				ft_mlx_init.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \
				libft/ft_atoi.c \
				libft/ft_bzero.c \
	   			libft/ft_calloc.c \
	   			libft/ft_isdigit.c \
	   			libft/ft_isspace.c \
	   			libft/ft_memcpy.c \
	   			libft/ft_memset.c \
	   			libft/ft_putstr_fd.c \
	   			libft/ft_split.c \
	   			libft/ft_strcmp.c \
				
# MINILIBX CONFIGURATION
MLX_PATH	=	minilibx-linux/
MLX_NAME	=	libmlx.a
MLX_HEADER	=   $(MLX_PATH)/mlx.h
MLX			=	$(MLX_PATH)$(MLX_NAME)

# OBJECT FILES
OBJ_DIR 	=	objs
OBJS		=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

# HEADER FILES
INCS		=	-I includes -I$(MLX_PATH)
# INCS = -I includes

GREEN 		=	\033[38;5;082;1m
END			=	\033[0m

.PHONY: all clean fclean re

all: $(MLX) $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Compiling $(NAME)...$(END)"
	@$(CC) $(OBJS) $(CFLAGS) $(LIBX_FLAGS) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/libft
	@mkdir -p $(OBJ_DIR)/get_next_line

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
