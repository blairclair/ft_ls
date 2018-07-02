/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reg_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:06:30 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/26 14:09:20 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include "libft/printf_functions/ft_printf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

char     *ft_strcmp_ls_i(char *ss1, char *ss2)
{
	int    temp_s1;
	int    temp_s2;

	temp_s1 = ft_atoi(ss1);
	temp_s2 = ft_atoi(ss2);
	if (ss1 == ss2)
		return (0);
	else if (ss1 > ss2)
		return (ss2);
	else
		return (ss1);
}

char	*ft_strcmp_ls(char *ss1, char *ss2)
{
	char    *temp_s1;
	char    *temp_s2;

	temp_s1 = ss1;
	temp_s2 = ss2;
	while (*ss1 != '\0' || *ss2 != '\0')
	{
		if (*ss1 == *ss2)
		{
			ss1 = ss1 + 1;
			ss2 = ss2 + 1;
		}
		else
		{
			if (*ss1 > *ss2)
				return (temp_s2);
			else
				return (temp_s1);
		}
	}
	return (NULL);
}

void    display_ls(char **arreg)
{
	int i;

	i = 0;
	while (arreg[i])
	{
		ft_printf("%s\n", arreg[i]);
		i++;
	}
}

char    **sort_reg(char **arreg)
{
	int     i;
	int     j;
	char    *x;

	j = 0;
	i = 1;
	while (arreg[i])
	{
		x = arreg[i];
		j = i - 1;
		while (j >= 0 && ft_strcmp_ls(arreg[j], x) == x)
		{
			arreg[j + 1] = arreg[j];
			j--;
		}
		arreg[j + 1] = x;
		i++;
	}
	return (arreg);
}


int get_num_reg(char *arg)
{
	struct dirent *test;
	DIR *dir1;
	int     i;

	i = 0;
	if ((dir1 = opendir(arg)) == NULL)
	{
		return (0);
	}
	while (1)
	{
		test = readdir(dir1);
		if (!test)
			break ;
		if (test->d_name[0] == '.')
			test = readdir(dir1);
		else
			i += ft_strlen(test->d_name);
	}
	closedir(dir1);
	return (i);
}

int get_num_date(char *arg)
{
	struct dirent *test;
	DIR *dir1;
	int     i;

	i = 0;
	if ((dir1 = opendir(arg)) == NULL)
	{
		return (0);
	}
	while ((test = readdir(dir1)) != NULL)
	{
		if (test->d_name[0] != '.')
			i++;
	}
	closedir(dir1);
	return (i);
}

int ls_reg(char *arg)
{
	struct dirent   *test;
	DIR             *dir1;
	char            **arreg;
	int             i;

	if ((arreg = malloc(sizeof(arreg) * get_num_reg(arg) + 1)) == NULL)
		return (0);
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
			arreg[i] = test->d_name;
			i++;
		}
	}
	arreg[i] = NULL;
	sort_reg(arreg);
	display_ls(arreg);
	free(arreg);
	closedir(dir1);
	return (0);
}

