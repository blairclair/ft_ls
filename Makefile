CC=gcc
CFLAGS=
SRCS=libft/ft_putchar.c\
libft/ft_strjoin.c\
libft/ft_strcat.c\
libft/ft_putstr.c\
libft/ft_putnbr.c\
libft/ft_strcmp.c\
libft/ft_toupper.c\
libft/ft_strlen.c\
libft/ft_itoa_base.c\
libft/ft_isdigit.c\
libft/ft_strcpy.c\
libft/ft_isalpha.c\
libft/ft_atoi.c\
libft/ft_strtoupper.c\
libft/ft_bzero.c\
libft/ft_memalloc.c\
libft/ft_strnew.c\
libft/ft_strdup.c\
libft/ft_memmove.c\
libft/ft_strchr.c\
libft/ft_strncpy.c\
libft/ft_strsplit.c\
libft/printf_functions/ft_putulong.c\
libft/printf_functions/ft_ltoa_base.c\
libft/printf_functions/ft_ultoa_base.c\
libft/printf_functions/ft_itoa.c\
libft/printf_functions/ft_strrev.c\
libft/printf_functions/parse.c\
libft/printf_functions/flags_1.c\
libft/printf_functions/ft_putnbr_pr.c\
libft/printf_functions/flags2.c\
libft/printf_functions/get_d.c\
libft/printf_functions/get_x.c\
libft/printf_functions/get_x2.c\
libft/printf_functions/get_cs.c\
libft/printf_functions/get_op.c\
libft/printf_functions/get_loc_value.c\
libft/printf_functions/get_num_lets.c\
libft/printf_functions/get_sizes.c\
libft/printf_functions/print_extra_flags.c\
libft/printf_functions/print_extra_stuff.c\
libft/printf_functions/ft_printf.c\
recurs_ls.c\
reg_ls.c\
hid_ls.c\
time_ls.c\
conv_time.c\
line_ls.c\
g_ls.c\
be_free.c\
ls_args.c\
get_file_nums.c\
sort_stuff.c\
conv_date.c\
sort_line.c\
get_permissions.c\
extra_line_info.c\
ft_ls.c

NAME=ft_ls

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) -c $(SRCS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS)
clean:
	/bin/rm -f *.o
	make -C libft/printf_functions/ clean
	make -C libft/ clean
fclean: clean
	/bin/rm -f $(NAME)
	make -C libft/printf_functions/ fclean
	make -C libft/ fclean

re: fclean all
