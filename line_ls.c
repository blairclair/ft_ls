/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 18:37:09 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/26 14:08:28 by agrodzin         ###   ########.fr       */
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

void    user_perm(char *perm, struct stat statcheck)
{
	if (statcheck.st_mode & S_IRUSR)
		perm[1] = 'r';
	else
		perm[1] = '-';
	if (statcheck.st_mode & S_IWUSR)
		perm[2] = 'w';
	else 
		perm[2] = '-';
	if (statcheck.st_mode & S_IXUSR)
		perm[3] = 'x';
	else
		perm[3] = '-';
}

void    group_perm(char *perm, struct stat statcheck)
{
	if (statcheck.st_mode & S_IRGRP)
		perm[4] = 'r';
	else
		perm[4] = '-';
	if (statcheck.st_mode & S_IWGRP)
		perm[5] = 'w';
	else
		perm[5] = '-';
	if (statcheck.st_mode & S_IXGRP)
		perm[6] = 'x';
	else
		perm[6] = '-';
}

void    other_perm(char *perm, struct stat statcheck)
{
	if (statcheck.st_mode & S_IROTH)
		perm[7] = 'r';
	else
		perm[7] = '-';
	if (statcheck.st_mode & S_IWOTH)
		perm[8] = 'w';
	else
		perm[8] = '-';
	if (statcheck.st_mode & S_IXOTH)
		perm[9] = 'x';
	else
		perm[9] = '-';
	perm[10] = '\0';
}

char    *get_perm(char *perm, struct stat statcheck)
{
	if (S_ISDIR(statcheck.st_mode))
		perm[0] = 'd';
	else
		perm[0] = '-'; 
	user_perm(&*perm, statcheck);
	group_perm(&*perm, statcheck);
	other_perm(&*perm, statcheck);
	return (perm);
}

int     get_num(struct stat statcheck)
{
	int numlink;

	numlink = statcheck.st_nlink;
	return (numlink);
}

char    *get_user(struct stat statcheck)
{
	struct  passwd *pwd;
	unsigned int    iduser;
	char        *pwname2;

	iduser = statcheck.st_uid;
	pwd = getpwuid(iduser);
	pwname2 = pwd->pw_name;
	pwname2[ft_strlen(pwd->pw_name) + 1] = '\0';
	return (pwname2);
}

char    *get_group(struct stat statcheck)
{
	struct  group *grp;
	unsigned int    idgroup;
	char        *strgrp;

	idgroup = statcheck.st_gid;
	grp = getgrgid(idgroup);
	strgrp = grp->gr_name;
	strgrp[ft_strlen(grp->gr_name) + 1] = '\0';
	return (strgrp);
}

int     get_file_size(struct stat statcheck)
{
	int     bsize;

	bsize = statcheck.st_size;
	return (bsize);
}

char    *get_date(char *date, struct stat statcheck)
{
	int     i;
	char    *date2;
	int     j;

	j = 0;
	i = 4;
	date2 = malloc(18);

	date = ft_strdup(ctime(&statcheck.st_mtime));
	while (i < 19)
	{
		date2[j] = date[i];
		j++;
		i++;
	}
	date2[j] = '\0';
	return (date2);
}


char    **get_arr(char *arg, struct line_stuff *lstuff)
{
	struct dirent   *test;
	DIR             *dir1;
	char            **arreg;
	int             i;
	struct stat statcheck;

	lstuff->realname = malloc(1);
	arreg = malloc(sizeof(arreg) * get_num_reg(arg) + 1);
	lstuff->perm = malloc(sizeof(lstuff) * (get_num_date(arg)  + 1));
	lstuff->user = malloc(sizeof(lstuff) * (get_num_date(arg) + 1));
	lstuff->group = malloc(sizeof(lstuff) * (get_num_date(arg) + 1));
	lstuff->date = malloc(sizeof(lstuff) *(get_num_date(arg) + 1));
	lstuff->num = malloc(sizeof(lstuff) *(get_num_date(arg) + 1));
	lstuff->bsize = malloc(sizeof(lstuff) *(get_num_date(arg) + 1));
	lstuff->size_padding = malloc(sizeof(lstuff) *(get_num_date(arg) + 1));
	i = 0;
	if ((dir1 = opendir(arg)) == NULL)
	{
		ft_printf("ls: %s: no such file or directory\n", arg);
		return (0);
	}
	while ((test = readdir(dir1)) != NULL )
	{
		if (test->d_name[0] != '.')
		{
			ft_bzero(lstuff->realname, ft_strlen(lstuff->realname));
			lstuff->realname = ft_strjoin(lstuff->realname, arg);
			lstuff->realname =ft_strjoin(lstuff->realname, "/");
			lstuff->realname = ft_strjoin(lstuff->realname, test->d_name);
			stat(lstuff->realname, &statcheck);
			lstuff->perm[i] = malloc(sizeof(lstuff));
			arreg[i] = test->d_name;
			lstuff->perm[i] = get_perm(lstuff->perm[i], statcheck);
			lstuff->user[i] = get_user(statcheck);
			lstuff->group[i] = get_group(statcheck);
			lstuff->date[i] = get_date(lstuff->date[i], statcheck);
			lstuff->num[i] = get_num(statcheck);
			lstuff->bsize[i] = get_file_size(statcheck);
			lstuff->size_padding[i] = get_num_len(lstuff->bsize[i]);

			i++;
		}
	}
	arreg[i] = NULL;
	lstuff->perm[i] = NULL;
	lstuff->user[i] = NULL;
	lstuff->group[i] = NULL;
	lstuff->date[i] = NULL;
	return (arreg);
}

char    **sort_line(char **arreg, struct line_stuff *lstuff)
{
	int     i;
	int     j;
	char    *x2;
	struct sortstuff s_stuff;

	j = 0;
	i = 1;

	while (arreg[i])
	{
		x2 = arreg[i];
		s_stuff.bsizesort = lstuff->bsize[i];
		s_stuff.datesort = lstuff->date[i];
		s_stuff.groupsort = lstuff->group[i];
		s_stuff.namesort = lstuff->name[i];
		s_stuff.numsort = lstuff->num[i];
		s_stuff.permsort = lstuff->perm[i];
		s_stuff.usersort = lstuff->user[i];
		j = i - 1;
		while (j >= 0 && ft_strcmp_ls(arreg[j], x2) == x2)
		{
			arreg[j + 1] = arreg[j];
			lstuff->bsize[j + 1] = lstuff->bsize[j];
			lstuff->date[j + 1] = lstuff->date[j];
			lstuff->group[j + 1] = lstuff->group[j];
			lstuff->name[j + 1] = lstuff->name[j];
			lstuff->num[j + 1] = lstuff->num[j];
			lstuff->perm[j + 1] = lstuff->perm[j];
			lstuff->user[j + 1] = lstuff->user[j];
			j--;
		}
		arreg[j + 1] = x2;
		lstuff->bsize[j + 1] = s_stuff.bsizesort;
		lstuff->date[j + 1] = s_stuff.datesort;
		lstuff->group[j + 1] = s_stuff.groupsort;
		lstuff->name[j + 1] = s_stuff.namesort;
		lstuff->num[j + 1] = s_stuff.numsort;
		lstuff->perm[j + 1] = s_stuff.permsort;
		lstuff->user[j + 1] = s_stuff.usersort;
		i++;
	}
	return (arreg);
}


int   sort_size(int *bsize)
{
	int     i;
	int     j;
	int    x;

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


int ls_l(char *arg, struct line_stuff *lstuff)
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
		// padding = ft_itoa(padnum - get_num_len(lstuff->bsize[i]));
		ft_printf("%s %d %s %s%s %d %s %s\n", lstuff->perm[i], lstuff->num[i], lstuff->user[i], 
				lstuff->group[i], padding, lstuff->bsize[i], lstuff->date[i], lstuff->name[i]);
		i++;
	} 
	j = i;
	/*
	while (i > 0)
	{
		free(lstuff->perm[i]);
		i--;
	}
	free(lstuff->perm);
	free(lstuff->user);
	free(lstuff->group);
	free(lstuff->date);
	free(lstuff->name);*/
	return (0);
}
