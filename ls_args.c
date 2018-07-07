/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 08:28:10 by agrodzin          #+#    #+#             */
/*   Updated: 2018/07/06 08:28:12 by agrodzin         ###   ########.fr       */
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

int		check_minus(char *arg_list)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
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
	return (check);
}

char	**get_path(char *arg_list)
{
	int		j;
	char	**path;
	int		k;
	char	*al;
	int		check;

	check = check_minus(arg_list);
	path = malloc(200);
	j = 0;
	k = 0;
	if (ft_strlen(arg_list) == 0 || (ft_strlen(arg_list) > 0 &&
	 ft_strlen(arg_list) <= 3 && check == 1))
	{
		path[j] = malloc(2);
		ft_strcpy(path[j], ".");
	}
	else
	{
		al = ft_memalloc(200);
		if (check == 1)
			al = ft_memmove(al, arg_list + 2, ft_strlen(arg_list) - 2);
		else
			al = ft_memmove(al, arg_list, ft_strlen(arg_list));
		path = ft_strsplit(al, ' ');	
	}
	return (path);
}

void	call_args(struct s_dirstuff *lsdirs, struct s_line_stuff *lstuff,
					struct s_timestuff *ts, char **path)
{
	int i;

	i = 0;
	while (path[i])
	{
		if (lsdirs->r2 == 1)
			ls_r2(path[i], lsdirs);
		else if (lsdirs->a == 1)
			ls_a(path[i]);
		else if (lsdirs->r == 1)
			ls_r(path[i]);
		else if (lsdirs->t == 1)
			ls_ti(path[i], ts);
		else if (lsdirs->l == 1)
			ls_l(path[i], lstuff);
		else if (lsdirs->f == 1)
			ls_f(path[i]);
		else if (lsdirs->d == 1)
			ls_d(path[i]);
		else if (lsdirs->g == 1)
			ls_g(path[i], lstuff);
		else if (lsdirs->nt == 1)
		{
			ft_printf("ls: illegal option -%s\nusage:ls", path[i]);
			ft_printf(" [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
		}
		else
			ls_reg(path[i]);
		i++;
	}
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
	char	**path;

	i = 0;
	path = get_path(arg_list);
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
