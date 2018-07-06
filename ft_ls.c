/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:02:29 by agrodzin          #+#    #+#             */
/*   Updated: 2018/07/05 12:27:18 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include "ft_ls.h"
#include "libft/printf_functions/ft_printf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <sys/xattr.h>

char	*get_path(char *arg_list, int i, int check)
{
	char	*path;

	if (ft_strlen(arg_list) > 3 && i != (int)ft_strlen(arg_list))
	{
		path = malloc(ft_strlen(arg_list) - i);
		ft_memmove(path, arg_list + (i + 2), ft_strlen(arg_list) - (i + 2));
	}
	else if (check == 0)
	{
		path = malloc(ft_strlen(arg_list) + 1);
		ft_strcpy(path, arg_list);
	}
	else
	{
		path = malloc(2);
		ft_strcpy(path, ".");
	}
	return (path);
}

char	*parse_args2(char *arg_list)
{
	int		i;
	char	*path;
	int		check;

	check = 0;
	i = 0;
	while (arg_list[i])
	{
		if (arg_list[i] == '-' && (arg_list[i + 1] == 'R' ||
			arg_list[i + 1] == 'a' || arg_list[i + 1] == 'r' ||
			arg_list[i + 1] == 't' || arg_list[i + 1] == 'l' ||
			arg_list[i + 1] == 'f' || arg_list[i + 1] == 'd' ||
			arg_list[i + 1] == 'g'))
		{
			check = 1;
			break ;
		}
		i++;
	}
	path = get_path(arg_list, i, check);
	return (path);
}

void	call_args(struct s_dirstuff *lsdirs, struct s_line_stuff *lstuff,
					struct s_timestuff *ts, char *path)
{
	if (lsdirs->r2 == 1)
		ls_r2(path, lsdirs);
	else if (lsdirs->a == 1)
		ls_a(path);
	else if (lsdirs->r == 1)
		ls_r(path);
	else if (lsdirs->t == 1)
		ls_ti(path, ts);
	else if (lsdirs->l == 1)
		ls_l(path, lstuff);
	else if (lsdirs->f == 1)
		ls_f(path);
	else if (lsdirs->d == 1)
		ls_d(path);
	else if (lsdirs->g == 1)
		ls_g(path, lstuff);
	else if (lsdirs->nt == 1)
	{
		ft_printf("ls: illegal option -%s\nusage:ls", path);
		ft_printf(" [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
	}
	else
		ls_reg(path);
}

void	check_flags(char *arg_list, int i, struct s_dirstuff *lsdirs)
{
	if (arg_list[i] == 'R')
		lsdirs->r2 = 1;
	else if (arg_list[i] == 'a')
		lsdirs->a = 1;
	else if (arg_list[i] == 'r')
		lsdirs->r = 1;
	else if (arg_list[i] == 't')
		lsdirs->t = 1;
	else if (arg_list[i] == 'l')
		lsdirs->l = 1;
	else if (arg_list[i] == 'f')
		lsdirs->f = 1;
	else if (arg_list[i] == 'd')
		lsdirs->d = 1;
	else if (arg_list[i] == 'g')
		lsdirs->g = 1;
	else
		lsdirs->nt = 1;
}

void	parse_args(char *arg_list, struct s_dirstuff *lsdirs,
					struct s_timestuff *ts, struct s_line_stuff *lstuff)
{
	int		i;
	char	*path;

	i = 0;
	path = parse_args2(arg_list);
	while (arg_list[i])
	{
		if (arg_list[i] == '-')
		{
			i++;
			if (arg_list[i] == '1')
				i++;
			check_flags(arg_list, i, lsdirs);
		}
		i++;
	}
	call_args(lsdirs, lstuff, ts, path);
	free(path);
}

void	define_vars(struct s_dirstuff *lsdirs,
					struct s_line_stuff *lstuff, struct s_timestuff *ts)
{
	lsdirs->arreg = malloc(sizeof(lsdirs->arreg) * get_num_reg(".") + 1);
	ts->nantime = NULL;
	lsdirs->newdir = NULL;
	lsdirs->num_dir = 0;
	lsdirs->arrnum = 0;
	lsdirs->dir_names = malloc(200);
	lstuff->name = NULL;
	lstuff->numblocks = 0;
	lsdirs->a = 0;
	lsdirs->l = 0;
	lsdirs->r = 0;
	lsdirs->r2 = 0;
	lsdirs->reg = 0;
	lsdirs->t = 0;
	lsdirs->f = 0;
	lsdirs->d = 0;
	lsdirs->g = 0;
	lsdirs->nt = 0;
}

void	free_stuff(struct s_dirstuff *lsdirs,
					struct s_timestuff *ts)
{
	int	i;

	i = 0;
	if (lsdirs->t == 1)
	{
		i = 0;
		while (ts->regtime[i])
		{
			free(ts->regtime[i]);
			i++;
		}
		i = 0;
		free(ts->regtime);
		free(ts->nantime);
	}
	free(lsdirs->dir_names);
	free(lsdirs->arreg);
}

int		main(int argc, char *argv[])
{
	struct s_dirstuff	lsdirs;
	struct s_timestuff	ts;
	int					i;
	char				*arg_list;
	struct s_line_stuff	lstuff;

	arg_list = "";
	i = 3;
	define_vars(&lsdirs, &lstuff, &ts);
	arg_list = ft_strjoin(arg_list, argv[1]);
	if (argc == 1 || !ft_strcmp(arg_list, "-1"))
		ls_reg(".");
	else
	{
		while (i < argc + 1)
		{
			ft_strcat(arg_list, argv[i - 1]);
			i++;
		}
		parse_args(arg_list, &lsdirs, &ts, &lstuff);
	}
	free_stuff(&lsdirs, &ts);
	free(arg_list);
	return (0);
}
