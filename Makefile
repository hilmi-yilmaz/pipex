# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: hyilmaz <hyilmaz@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/02 12:45:21 by hyilmaz       #+#    #+#                  #
#    Updated: 2021/11/21 21:07:20 by hyilmaz       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

ifdef DEBUG
CFLAGS := $(CFLAGS) -g -fsanitize=address
endif

ifdef BONUS
SRC_FILES_EXTRA = pipex_bonus.c processes_bonus.c
else
SRC_FILES_EXTRA = pipex.c processes.c
endif

# Mandatory
SRC_DIR = src
SRC_FILES = parse_input.c \
			utils.c \
			get_filenames.c \
			free_data.c \
			print_data.c

SRC_FILES := $(SRC_FILES) $(SRC_FILES_EXTRA)

HEADER_FILES = 	pipex.h \
				parse_input.h \
				processes.h \
				utils.h \
				get_filenames.h \
				free_data.h \
				print_data.h

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
