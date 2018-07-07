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

int		main(int argc, char *argv[])
{
	struct s_dirstuff	lsdirs;
	struct s_timestuff	ts;
	int					i;
	char				*arg_list;
	struct s_line_stuff	lstuff;

	arg_list = "";
	i = 2;
	define_vars(&lsdirs, &lstuff, &ts);
	arg_list = malloc(200);
	if (argc == 1 || !ft_strcmp(arg_list, "-1"))
		ls_reg(".");
	else
	{
		while (i < argc + 1)
		{
			ft_strcat(arg_list, argv[i - 1]);
			ft_strcat(arg_list, " ");
			i++;
		}
		parse_args(arg_list, &lsdirs, &ts, &lstuff);
	}
	free_stuff(&lsdirs);
	free(arg_list);
	return (0);
}
