/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 09:04:06 by agrodzin          #+#    #+#             */
/*   Updated: 2018/07/06 09:04:07 by agrodzin         ###   ########.fr       */
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

void	sort_line_p1(struct s_sortstuff *s_stuff, struct s_line_stuff *lstuff,
					int i)
{
	s_stuff->bsizesort = lstuff->bsize[i];
	s_stuff->datesort = lstuff->date[i];
	s_stuff->groupsort = lstuff->group[i];
	s_stuff->namesort = lstuff->name[i];
	s_stuff->numsort = lstuff->num[i];
	s_stuff->permsort = lstuff->perm[i];
	s_stuff->usersort = lstuff->user[i];
	s_stuff->linksort = lstuff->poss_link[i];
}

void	sort_line_p2(struct s_line_stuff *lstuff, int j)
{
	lstuff->bsize[j + 1] = lstuff->bsize[j];
	lstuff->date[j + 1] = lstuff->date[j];
	lstuff->group[j + 1] = lstuff->group[j];
	lstuff->name[j + 1] = lstuff->name[j];
	lstuff->num[j + 1] = lstuff->num[j];
	lstuff->perm[j + 1] = lstuff->perm[j];
	lstuff->user[j + 1] = lstuff->user[j];
	lstuff->poss_link[j + 1] = lstuff->poss_link[j];
}

void	sort_line_p3(struct s_sortstuff *s_stuff, struct s_line_stuff *lstuff,
					int j)
{
	lstuff->bsize[j + 1] = s_stuff->bsizesort;
	lstuff->date[j + 1] = s_stuff->datesort;
	lstuff->group[j + 1] = s_stuff->groupsort;
	lstuff->name[j + 1] = s_stuff->namesort;
	lstuff->num[j + 1] = s_stuff->numsort;
	lstuff->perm[j + 1] = s_stuff->permsort;
	lstuff->user[j + 1] = s_stuff->usersort;
	lstuff->poss_link[j + 1] = s_stuff->linksort;
}

char	**sort_line(char **arreg, struct s_line_stuff *lstuff)
{
	int					i;
	int					j;
	char				*x2;
	struct s_sortstuff	s_stuff;

	j = 0;
	i = 1;
	while (arreg[i])
	{
		x2 = arreg[i];
		sort_line_p1(&s_stuff, lstuff, i);
		j = i - 1;
		while (j >= 0 && ft_strcmp_ls(arreg[j], x2) == x2)
		{
			arreg[j + 1] = arreg[j];
			sort_line_p2(lstuff, j);
			j--;
		}
		arreg[j + 1] = x2;
		sort_line_p3(&s_stuff, lstuff, j);
		i++;
	}
	return (arreg);
}

int		sort_size(int *bsize)
{
	int	i;
	int	j;
	int	x;

	j = 0;
	i = 1;
	while (bsize[i])
	{
		x = bsize[i];
		j = i - 1;
		while (j >= 0 && bsize[j] < x)
		{
			bsize[j + 1] = bsize[j];
			j--;
		}
		bsize[j + 1] = x;
		i++;
	}
	return (bsize[0]);
}
