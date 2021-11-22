# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: hyilmaz <hyilmaz@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/02 12:45:21 by hyilmaz       #+#    #+#                  #
#    Updated: 2021/11/23 00:12:08 by hyilmaz       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


# Compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
DBGFLAGS = -g -fsanitize=address


# Project sources and headers
ifdef BONUS
SRC_FILES_EXTRA = check_input_bonus.c execute_commands_bonus.c processes_bonus.c
HEADER_FILES_EXTRA = processes_bonus.h
else
SRC_FILES_EXTRA = check_input.c execute_commands.c 
endif

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

# Release Object files
REL_OBJ_DIR = rel_obj
REL_OBJ_FILES = $(SRC_FILES:%.c=$(REL_OBJ_DIR)/%.o)
NAME = pipex

# Debug build settings
DBG_DIR = obj_debug
DBG_OBJ_FILES = $(SRC_FILES:%.c=$(DBG_DIR)/%.o)
DBGEXE = pipex_debug

# Libft
LIBFT_DIR = $(SRC_DIR)/libft
LIBFT = libft.a

# Set VPATH to look into src directory
VPATH = src

# Default build
all: $(REL_OBJ_DIR) $(LIBFT) $(NAME)

# Debug rules
debug: $(DBG_DIR) $(LIBFT) $(DBGEXE)

######################
# Create directories #
######################
$(REL_OBJ_DIR):
	mkdir -p $@
	mkdir -p $@/utils
	mkdir -p $@/parser

$(DBG_DIR):
	mkdir -p $@
	mkdir -p $@/utils
	mkdir -p $@/parser

###############
# Libft Build #
###############
$(LIBFT):
	make -C $(LIBFT_DIR)

###############
# Debug Build #
###############
$(DBGEXE): $(DBG_OBJ_FILES)
	$(CC) $(CFLAGS) $(DBGFLAGS) $^ $(LIBFT_DIR)/$(LIBFT) -o $@

$(DBG_OBJ_FILES): $(DBG_DIR)/%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) $(DBGFLAGS) -c $< -o $@

#################
# Release Build #
#################
$(NAME): $(REL_OBJ_FILES)
	$(CC) $(CFLAGS) $^ $(LIBFT_DIR)/$(LIBFT) -o $@

$(REL_OBJ_FILES): $(REL_OBJ_DIR)/%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $< -o $@

bonus:
	$(MAKE) BONUS=1 all

debug_bonus:
	$(MAKE) BONUS=1 debug

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(REL_OBJ_DIR) $(DBG_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME) $(DBGEXE)

re: fclean all

.PHONY: all clean fclean re bonus debug
