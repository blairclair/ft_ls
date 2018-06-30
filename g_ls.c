/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_ls.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 13:48:17 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/28 13:48:18 by agrodzin         ###   ########.fr       */
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


int ls_g(char *arg, struct line_stuff *lstuff)
{
	int     i;
	char    *padding;
	int     padnum;
	int     j;
	int     k;

	i = 0;
	k = 0;
	if ((lstuff->name = get_arr(arg, lstuff)) == 0)
		return (0);
	sort_line(lstuff->name, lstuff);
	padnum = sort_size(lstuff->size_padding);
	while (lstuff->name[i])
	{
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
			ft_strcpy(padding, " ");
		}
		ft_printf("%s %d %s%s %d %s %s\n", lstuff->perm[i], lstuff->num[i], lstuff->group[i], padding, lstuff->bsize[i], lstuff->date[i], lstuff->name[i]);
		i++;
	} 
	return (0);
}
