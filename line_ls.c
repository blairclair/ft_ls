/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 18:37:09 by agrodzin          #+#    #+#             */
/*   Updated: 2018/07/05 14:20:08 by agrodzin         ###   ########.fr       */
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

void	get_num_blocks(struct s_line_stuff *lstuff, struct stat statcheck)
{
	int	nb;

	nb = statcheck.st_blocks;
	lstuff->numblocks += nb;
}

void	define_lstuff(struct s_line_stuff *lstuff, char *arg)
{
	lstuff->realname = malloc(30);
	lstuff->name = malloc(sizeof(lstuff->name) * get_num_reg(arg) + 1);
	lstuff->perm = malloc(sizeof(lstuff) * (get_num_date(arg) * 10 + 1));
	lstuff->user = malloc(sizeof(lstuff) * (get_num_date(arg) * 8 + 1));
	lstuff->group = malloc(sizeof(lstuff) * (get_num_date(arg) * 15 + 1));
	lstuff->date = malloc(sizeof(lstuff) * (get_num_date(arg) * 8 + 1));
	lstuff->num = malloc(sizeof(lstuff) * (get_num_date(arg) * 5 + 1));
	lstuff->bsize = malloc(sizeof(lstuff) * (get_num_date(arg) * 5 + 1));
	lstuff->size_padding = malloc(sizeof(lstuff) * get_num_date(arg) * 10 + 1);
	lstuff->poss_link = malloc(sizeof(lstuff) * get_num_date(arg) * 10 + 1);
}

char	*get_link(struct stat statcheck, struct s_line_stuff *lstuff, int i)
{
	char	*poslink;
	char	*pl2;


	if (S_ISLNK(statcheck.st_mode))
	{
		poslink = malloc(200);
		pl2 = malloc(200);
		ft_strcpy(poslink, "-> ");
		readlink(lstuff->realname, pl2, 200);
		ft_strcat(poslink, pl2);
	}
	else
	{
		poslink = malloc(2);
		ft_strcpy(poslink, " ");
	}
	return (poslink);

}

int		get_line_arr(struct s_line_stuff *lstuff, struct dirent *test,
					char *arg, int i)
{
	struct stat statcheck;

	if (test->d_name[0] != '.')
	{
		ft_bzero(lstuff->realname, ft_strlen(lstuff->realname));
		lstuff->realname = ft_strcat(lstuff->realname, arg);
		lstuff->realname = ft_strcat(lstuff->realname, "/");
		lstuff->realname = ft_strcat(lstuff->realname, test->d_name);
		lstat(lstuff->realname, &statcheck);
		lstuff->perm[i] = malloc(sizeof(lstuff) * 15);
		lstuff->name[i] = test->d_name;
		lstuff->perm[i] = get_perm(lstuff->perm[i], statcheck);
		lstuff->user[i] = get_user(statcheck);
		lstuff->group[i] = get_group(statcheck);
		lstuff->date[i] = get_date(lstuff->date[i], statcheck);
		lstuff->num[i] = get_num(statcheck);
		lstuff->bsize[i] = get_file_size(statcheck);
		lstuff->size_padding[i] = get_num_len(lstuff->bsize[i]);
		lstuff->poss_link[i] = get_link(statcheck, lstuff, i);
		get_num_blocks(lstuff, statcheck);
		i++;
	}
	return (i);
}



char	**get_arr(char *arg, struct s_line_stuff *lstuff)
{
	struct dirent	*test;
	DIR				*dir1;
	int				i;

	define_lstuff(lstuff, arg);
	i = 0;
	ft_strcpy(lstuff->realname, " ");
	if ((dir1 = opendir(arg)) == NULL)
	{
		no_perm(arg);
		return (0);
	}
	while ((test = readdir(dir1)) != NULL)
		i = get_line_arr(lstuff, test, arg, i);
	lstuff->name[i] = NULL;
	lstuff->perm[i] = NULL;
	lstuff->user[i] = NULL;
	lstuff->group[i] = NULL;
	lstuff->date[i] = NULL;
	closedir(dir1);
	return (lstuff->name);
}

int		ls_l(char *arg, struct s_line_stuff *lstuff)
{
	int		i;
	char	*padding;
	int		padnum;
	int		j;
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
		ft_printf("%s %d %s %s%s %d %s %s %s\n", lstuff->perm[i], lstuff->num[i],
					lstuff->user[i], lstuff->group[i], padding,
					lstuff->bsize[i], lstuff->date[i], lstuff->name[i], lstuff->poss_link[i]);
		i++;
	}
//	display_ls(lstuff->poss_link);
	j = i;
	free(padding);
	free_l(lstuff);
	return (0);
}
