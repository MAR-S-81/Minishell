NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I.

LIBFT = ./libft/libft.a

OBJ_DIR = objs

SRC = \
	srcs/clean_exit.c \
	srcs/parsing/parsing.c \
	srcs/parsing/lexer_utils.c \
	srcs/parsing/expander_utils.c \
	srcs/envp.c \

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: %.c minishell.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

clean:
	$(MAKE) clean -C libft
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
