/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_ls.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 13:48:17 by agrodzin          #+#    #+#             */
/*   Updated: 2018/07/06 09:54:47 by agrodzin         ###   ########.fr       */
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
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>

char	*get_padding(char *padding, int padnum,
					int i, struct s_line_stuff *lstuff)
{
	int	k;
	int	j;

	j = get_num_len(lstuff->bsize[i]);
	if (j < padnum)
	{
		k = 0;
		padding = malloc(padnum - j);
		while (j <= padnum)
		{
			padding[k] = ' ';
			j++;
			k++;
		}
	}
	else
	{
		padding = malloc(2);
		ft_strcpy(padding, " ");
	}
	return (padding);
}

int		ls_g(char *arg, struct s_line_stuff *lstuff)
{
	int		i;
	char	*padding;
	int		padnum;
	int		k;

	i = 0;
	k = 0;
	if ((lstuff->name = get_arr(arg, lstuff)) == 0)
		return (0);
	sort_line(lstuff->name, lstuff);
	padnum = sort_size(lstuff->size_padding);
	ft_printf("total %d\n", lstuff->numblocks);
	while (lstuff->name[i])
	{
		padding = get_padding(*&padding, padnum, i, lstuff);
		ft_printf("%s %d %s%s %d %s %s\n", lstuff->perm[i], lstuff->num[i],
					lstuff->group[i], padding, lstuff->bsize[i],
					lstuff->date[i], lstuff->name[i]);
		i++;
	}
	free(padding);
	return (0);
}
