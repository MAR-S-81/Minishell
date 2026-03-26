NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I.

LIBFT = ./libft/libft.a

OBJ_DIR = objs

SRC = \
    gnl/get_next_line_utils.c \
    gnl/get_next_line.c \
    srcs/builtins/builtins.c \
    srcs/builtins/cd.c \
    srcs/builtins/echo.c \
    srcs/builtins/env.c \
    srcs/builtins/exit.c \
    srcs/builtins/export.c \
    srcs/builtins/pwd.c \
    srcs/builtins/unset.c \
    srcs/parsing/parsing.c \
	srcs/parsing/utils/arger.c \
	srcs/parsing/utils/build_commands_utils.c \
	srcs/parsing/utils/expander_utils.c \
	srcs/parsing/utils/format_check_util.c \
	srcs/parsing/utils/lexer_utils.c \
	srcs/parsing/utils/nulizer_utils.c \
	srcs/parsing/utils/parsing_functions.c \
	srcs/parsing/utils/remove_quote_extend.c \
	srcs/parsing/here_doc_checker.c \
	srcs/parsing/ft_here_doc.c \
    srcs/clean_exit.c \
    srcs/envp.c \
    srcs/pipex_utils.c \
    srcs/pipex.c \
    srcs/readline.c \
    srcs/simple_cmd.c \
    srcs/utils.c \
    srcs/utils2.c \
	srcs/utils3.c \
	srcs/utils4.c \
	srcs/builtins/utils_builtins.c \
	main.c 

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

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
