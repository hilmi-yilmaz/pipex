# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: hyilmaz <hyilmaz@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/02 12:45:21 by hyilmaz       #+#    #+#                  #
#    Updated: 2021/11/22 15:44:09 by hyilmaz       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

ifdef DEBUG
CFLAGS := $(CFLAGS) -g -fsanitize=address
endif

ifdef BONUS
SRC_FILES_EXTRA = check_input_bonus.c execute_commands_bonus.c processes_bonus.c
HEADER_FILES_EXTRA = processes_bonus.h
else
SRC_FILES_EXTRA = check_input.c execute_commands.c 
endif

# Mandatory
SRC_DIR = src
SRC_FILES = pipex.c \
			parser/parse_input.c \
			parser/get_commands.c \
			parser/get_executable_with_full_path.c \
			parser/get_commands_from_argv.c \
			parser/get_filenames.c \
			processes.c \
			utils/utils.c \
			utils/free_data.c \
			utils/print_data.c

SRC_FILES := $(SRC_FILES) $(SRC_FILES_EXTRA)

HEADER_FILES = 	pipex.h \
				check_input.h \
				parser/parse_input.h \
				parser/get_commands.h \
				parser/get_executable_with_full_path.h \
				parser/get_commands_from_argv.h \
				parser/get_filenames.h \
				processes.h \
				execute_commands.h \
				utils/utils.h \
				utils/free_data.h \
				utils/print_data.h

HEADER_FILES := $(HEADER_FILES) $(HEADER_FILES_EXTRA)

OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

# Libft
LIBFT_DIR = $(SRC_DIR)/libft
LIBFT = libft.a

# Set VPATH to look into src directory
VPATH = src

# Program name
NAME = pipex

all: $(OBJ_DIR) $(LIBFT) $(NAME)

$(OBJ_DIR):
	mkdir -p $@
	mkdir -p $@/utils
	mkdir -p $@/parser

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ $(LIBFT_DIR)/$(LIBFT) -o $@

$(OBJ_FILES): $(OBJ_DIR)/%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $< -o $@

debug:
	$(MAKE) DEBUG=1 re

bonus:
	$(MAKE) BONUS=1 all

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
