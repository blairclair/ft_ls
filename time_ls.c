/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:33:39 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/26 14:09:37 by agrodzin         ###   ########.fr       */
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

char    **sort_time(char **arreg, char **arrtime)
{
	int     i;
	int     j;
	char    *x;
	char    *x2;

	j = 0;
	i = 1;

	while (arrtime[i])
	{
		x2 = arrtime[i];
		x = arreg[i];
		j = i - 1;
		while (j >= 0 && ft_strcmp_ls(arrtime[j], x2) == arrtime[j])
		{
			arrtime[j + 1] = arrtime[j];
			arreg[j + 1] = arreg[j];
			j--;
		}
		arrtime[j + 1] = x2;
		arreg[j + 1] = x;
		i++;
	}
	return (arreg);
}

int ls_ti(char *arg, struct timestuff *ts) 
{
	struct dirent   *test;
	DIR             *dir1;
	char            **arreg;
	int             i;
	struct stat     statcheck;
	time_t           ti;
	char             **date_num;

	arreg = malloc(get_num_reg(arg) + 1);
	ts->realtname = malloc(1);
	ts->nantime = malloc(sizeof(ts) * (get_num_date(arg) + 1));
	ts->regtime = malloc(sizeof(ts) * (get_num_date(arg) + 1)); 
	i = 0;
	if ((dir1 = opendir(arg)) == NULL)
	{
		ft_printf("ls: %s: no such file or directory\n", arg);
		return (0);
	}
	while ((test = readdir(dir1)) != NULL)
	{
		if (test->d_name[0] != '.')
		{
			ft_bzero(ts->realtname, ft_strlen(ts->realtname));
			ts->realtname = ft_strjoin(ts->realtname, arg);
			ts->realtname =ft_strjoin(ts->realtname, "/");
			ts->realtname = ft_strjoin(ts->realtname, test->d_name);
			arreg[i] = malloc(ft_strlen(test->d_name) + 1);
			arreg[i] = test->d_name;
			stat(ts->realtname, &statcheck);
			ts->regtime[i] = ft_strdup(ctime(&statcheck.st_mtime));
			ti = statcheck.st_mtimespec.tv_nsec;
			ts->nantime[i] = ti;
			i++;
		}
	}
	// ft_printf("rtime: %s", ts->regtime[0]);
	arreg[i] = NULL;
	ts->regtime[i] = NULL;
	ts->nantime[i] = '\0';
	// display_ls(ts->regtime);
	date_num = conv_full_date(arg, ts);
	sort_time(arreg, date_num);
	display_ls(arreg);
	
	free(arreg);
	free(ts->regtime);
	free(ts->nantime);
/*	while (arreg[i])
	{
		ft_printf("\n%s %s\n", arreg[i], date_num[i]);
		i++;
	}*/
//	closedir(dir1);

	return (0);
}
