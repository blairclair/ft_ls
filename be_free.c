/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   be_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 08:21:32 by agrodzin          #+#    #+#             */
/*   Updated: 2018/07/06 08:21:34 by agrodzin         ###   ########.fr       */
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

void	free_l(struct s_line_stuff *lstuff)
{
	int	i;

	free(lstuff->realname);
	i = 0;
	free(lstuff->name);
	while (lstuff->perm[i])
	{
		free(lstuff->perm[i]);
		i++;
	}
	free(lstuff->perm);
	i = 0;
	while (lstuff->date[i])
	{
		free(lstuff->date[i]);
		i++;
	}
	free(lstuff->user);
	free(lstuff->group);
	free(lstuff->date);
	free(lstuff->num);
	free(lstuff->bsize);
	free(lstuff->size_padding);
}

void	free_r2(struct s_dirstuff *r2dir)
{
	int	j;

	j = 0;
	free(r2dir->newdir);
	while (r2dir->dir_names[j])
	{
		free(r2dir->dir_names[j]);
		j++;
	}
	j = 0;
}

void	free_stuff(struct s_dirstuff *lsdirs)
{
	free(lsdirs->dir_names);
	free(lsdirs->arreg);
}

void	free_date(char **date_num, char **arreg, struct s_timestuff *ts)
{
	int	i;

	i = 0;/*
	while (date_num[i])
	{
		free(date_num[i]);
		i++;
	}*/
	free(date_num);
	free(arreg);
	i = 0;
	while (ts->regtime[i])
	{
		free(ts->regtime[i]);
		i++;
	}
	free(ts->regtime);
	free(ts->nantime);
}
