/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_ls.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 13:48:17 by agrodzin          #+#    #+#             */
/*   Updated: 2018/07/05 13:22:45 by agrodzin         ###   ########.fr       */
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
		ft_strcpy(padding, " ");
	return (padding);
}

int		get_total_size(struct s_line_stuff *lstuff)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (lstuff->bsize[i])
	{
		size += lstuff->bsize[i];
		//	printf("num: %d\n", lstuff->num[i]);
		i++;
	}
	return (size);
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
//	ft_printf("total %d\n", get_total_size(lstuff));
	padnum = sort_size(lstuff->size_padding);
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
