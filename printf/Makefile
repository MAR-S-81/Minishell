NAME    = libftprintf.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I.

SRC	=	ft_printf.c \
		ft_putnbr_hex_fd.c \
		ft_putnbr_unsign_fd.c \
		ft_putnbr_ptr_fd.c \
		ft_putstr_fd_edit.c \
		ft_putnbr_fd_edit.c \
		ft_putchar_fd_edit.c

OBJ        = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
