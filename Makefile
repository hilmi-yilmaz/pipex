CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRC_DIR = src
SRC_FILES = pipex.c \
			parse_input.c

HEADER_FILES = 	pipex.h \
				parse_input.h

OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = $(SRC_DIR)/libft
LIBFT = libft.a

VPATH = src

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

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all
	