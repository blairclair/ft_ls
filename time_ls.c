/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:33:39 by agrodzin          #+#    #+#             */
/*   Updated: 2018/07/05 16:00:31 by agrodzin         ###   ########.fr       */
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

int		get_s_num_ls(long long n)
{
	int	i;

	if (n < 0)
		i = 3;
	else
		i = 2;
	while ((n = n / 10))
		i++;
	i--;
	return (i);
}

char	*ft_ltoa_ls(long long n)
{
	char	*str;
	int		size;
	int		neg;

	neg = 1;
	if (n == '\0')
		return ("0");
	size = get_s_num_ls(n);
	str = malloc(size + 1);
	if (n < 0)
		neg = -1;
	str[size--] = '\0';
	while (n)
	{
		str[size--] = neg * (n % 10) + '0';
		n = n / 10;
	}
	if (neg == -1)
		str[size--] = '-';
	return (str);
}

int		sort_time1(char **arrtime, char **arreg, char *x2, int j)
{
	while (j >= 0 && ft_strcmp_ls(arrtime[j], x2) == arrtime[j])
	{
		arrtime[j + 1] = arrtime[j];
		arreg[j + 1] = arreg[j];
		j--;
	}
	return (j);
}

int		sort_time2(char **arrtime, char **arreg, char *x, int j)
{
	while (j >= 0 && ft_strcmp_ls(arreg[j], x) == arreg[j])
	{
		arreg[j + 1] = arreg[j];
		arrtime[j + 1] = arrtime[j];
		j--;
	}
	return (j);
}

char	**sort_time(char **arreg, char **arrtime)
{
	int		i;
	int		j;
	char	*x;
	char	*x2;

	j = 0;
	i = 1;
	while (arrtime[i])
	{
		x2 = arrtime[i];
		x = arreg[i];
		j = i - 1;
		if (ft_strcmp_ls(arrtime[j], x2))
			j = sort_time1(arrtime, arreg, x2, j);
		else
			sort_time2(arrtime, arreg, x, j);
		arrtime[j + 1] = x2;
		arreg[j + 1] = x;
		i++;
	}
	return (arreg);
}

int		define_time(char **arreg, char *arg, struct s_timestuff *ts, DIR *dir1)
{
	int				i;
	struct dirent	*test;
	struct stat		statcheck;

	i = 0;
	while ((test = readdir(dir1)) != NULL)
	{
		ft_bzero(ts->realtname, ft_strlen(ts->realtname));
		ts->realtname = ft_strjoin(ts->realtname, arg);
		ts->realtname = ft_strjoin(ts->realtname, "/");
		ts->realtname = ft_strjoin(ts->realtname, test->d_name);
		if (test->d_name[0] != '.')
		{
			arreg[i] = test->d_name;
			stat(ts->realtname, &statcheck);
			ts->regtime[i] = ft_strdup(ctime(&statcheck.st_mtime));
			ts->ntime = statcheck.st_mtimespec.tv_nsec;
			ts->nantime[i] = ft_ltoa_ls(ts->ntime);
			i++;
		}
	}
	return (i);
}

void	free_date(char **date_num, char **arreg)
{
	int	i;

	i = 0;
	while (date_num[i])
	{
		free(date_num[i]);
		i++;
	}
	free(date_num);
	free(arreg);
}

int		ls_ti(char *arg, struct s_timestuff *ts)
{
	char			**date_num;
	char			**arreg;
	DIR				*dir1;
	int				i;

	arreg = malloc(get_num_reg(arg) * sizeof(arreg) + 1);
	ts->realtname = malloc(2);
	ts->regtime = malloc(sizeof(ts->regtime) * (get_num_date(arg) * 24 + 1));
	ts->nantime = malloc(sizeof(ts->nantime) * get_num_date(arg) * 10 + 1);
	if ((dir1 = opendir(arg)) == NULL)
	{
		ft_printf("ls: %s: no such file or directory\n", arg);
		return (0);
	}
	ft_strcpy(ts->realtname, " ");
	i = define_time(arreg, arg, ts, dir1);
	arreg[i] = NULL;
	ts->nantime[i] = NULL;
	ts->regtime[i] = NULL;
	date_num = conv_full_date(arg, ts);
	sort_time(arreg, date_num);
	display_ls(arreg);
	free_date(date_num, arreg);
	closedir(dir1);
	return (0);
}
