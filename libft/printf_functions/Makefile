CC=gcc
HEADER=ft_printf.h
CFLAGS= -Wall -Werror -Wextra -c
SRCS=libft/ft_putchar.c\
libft/ft_putstr.c\
libft/ft_putnbr.c\
libft/ft_toupper.c\
libft/ft_strlen.c\
libft/ft_itoa_base.c\
libft/ft_isdigit.c\
libft/ft_strcpy.c\
libft/ft_isalpha.c\
libft/ft_atoi.c\
libft/ft_strcmp.c\
libft/ft_strtoupper.c\
ft_ltoa_base.c\
ft_strrev.c\
ft_itoa.c\
parse.c\
ft_ultoa_base.c\
ft_putulong.c\
flags_1.c\
ft_putnbr_pr.c\
flags2.c\
get_cs.c\
get_d.c\
get_op.c\
get_x.c\
get_x2.c\
ft_ltoa.c\
get_loc_value.c\
get_num_lets.c\
get_sizes.c\
print_extra_flags.c\
print_extra_stuff.c\
ft_printf.c
NAME=libftprintf.a
LIB=ar rc
OBJ=ft_putchar.o\
ft_putstr.o\
ft_putnbr.o\
ft_toupper.o\
ft_strlen.o\
ft_itoa_base.o\
ft_isdigit.o\
ft_strcpy.o\
ft_isalpha.o\
ft_atoi.o\
ft_strcmp.o\
ft_strtoupper.o\
ft_ltoa_base.o\
ft_strrev.o\
ft_itoa.o\
parse.o\
ft_ultoa_base.o\
ft_putulong.o\
flags_1.o\
ft_putnbr_pr.o\
flags2.o\
get_cs.o\
get_d.o\
get_op.o\
get_x.o\
get_x2.o\
ft_ltoa.o\
get_loc_value.o\
get_num_lets.o\
get_sizes.o\
print_extra_flags.o\
print_extra_stuff.o\
ft_printf.o

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -I $(HEADER)
	$(LIB) $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f *.o
	make -C libft/ clean

fclean:
	/bin/rm -f *.a *.o
	make -C libft/ fclean
	
re: fclean all
