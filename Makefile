# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 02:03:42 by jhurpy            #+#    #+#              #
#    Updated: 2023/07/23 00:12:41 by jhurpy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = @gcc
C_FLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
#S_FLAGS = -g -fsanitize=address,undefined,leak

# Commands
RM = @rm -rf
AR = ar rc

# ---------------------------------------------------------------------------- #

# Target library name and directories
NAME = pipex
LIBFT = ./libft/libft.a
SRC_DIR = src
SRC_FILES =	00_pipex.c \
			01_open_file.c \
			02_fork_process.c \
			03_execute_cmd.c

OBJ_DIR = obj
INC_DIR = include
LIBFT_DIR = ./libft
INCS = -I$(INC_DIR) -I$(LIBFT_DIR)

# Sources, objects and dependencies
SOURCES = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJECTS = $(SOURCES:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)

# ---------------------------------------------------------------------------- #

# Default target, build the library
all: $(LIBFT_DIR) $(NAME)

# Rule to build each personal library
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Object file build rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c $< -o $@

# Target library build rule
$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(C_FLAGS) $^ $(INCS) -o $(NAME)

# ---------------------------------------------------------------------------- #

# Target library name and directories BONUS
NAME_BONUS = pipex_bonus
LIBFT = ./libft/libft.a
SRC_DIR_BONUS = src_bonus
SRC_FILES_BONUS =	00_pipex_bonus.c \
					01_open_file_bonus.c \
					02_fork_process_bonus.c \
					03_execute_cmd_bonus.c

OBJ_DIR_BONUS = obj_bonus
INC_DIR_BONUS = include_bonus
LIBFT_DIR = ./libft
INCS_BONUS = -I$(INC_DIR_BONUS) -I$(LIBFT_DIR)

# Sources, objects and dependencies
SOURCES_BONUS = $(addprefix $(SRC_DIR_BONUS)/, $(SRC_FILES_BONUS))
OBJECTS_BONUS = $(SOURCES_BONUS:$(SRC_DIR_BONUS)%.c=$(OBJ_DIR_BONUS)/%.o)

# ---------------------------------------------------------------------------- #

# Default target, build the library
bonus: $(LIBFT_DIR) $(NAME_BONUS)

# Object file build rule
$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c $< -o $@

# Target library build rule
$(NAME_BONUS): $(OBJECTS_BONUS) $(LIBFT)
	$(CC) $(C_FLAGS) $^ $(INCS_BONUS) -o $(NAME_BONUS)

# ---------------------------------------------------------------------------- #

# Clean object files
clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(OBJ_DIR_BONUS)
	@make clean -C $(LIBFT_DIR)

# Clean object files and target library
fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)
	$(RM) $(LIBFT_DIR)/libft.a
	@make fclean -C $(LIBFT_DIR)

# Clean and rebuild the target library
re: fclean all bonus

# Check code style
norm:
	@norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*.c ;
	@norminette -R CheckDefine $(INC_DIR)/*.h ;
	@norminette -R CheckForbiddenSourceHeader $(SRC_DIR_BONUS)/*.c ;
	@norminette -R CheckDefine $(INC_DIR_BONUS)/*.h ;
	@norminette -R CheckForbiddenSourceHeader $(LIBFT_DIR)/src/*.c ;
	@norminette -R CheckDefine $(LIBFT_DIR)/includes/*.h

# Phony targets
.PHONY: all clean fclean re norm
