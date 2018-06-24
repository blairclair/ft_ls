/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 09:03:24 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/16 11:59:03 by agrodzin         ###   ########.fr       */
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

int		countdir(char *arg, struct s_dirstuff *r2dir)
{
	struct dirent   *test;
	DIR             *dir1;
	struct stat     statcheck;

	if ((dir1 = opendir(arg)) == NULL)
	{    return (r2dir->num_dir);
		closedir(dir1);
	}
	while ((test = readdir(dir1)) != NULL)
	{
		if (test->d_name[0] != '.')
		{
			r2dir->newdir = ft_strjoin(arg, "/");
			r2dir->newdir = ft_strjoin(r2dir->newdir, test->d_name);
			stat(r2dir->newdir, &statcheck);
			if (S_ISDIR(statcheck.st_mode))//checks if isdirectory
			{
				r2dir->dir_names[r2dir->arrnum] = malloc(50);
				r2dir->dir_names[r2dir->arrnum] = r2dir->newdir;
				r2dir->arrnum++;
				r2dir->num_dir++;
				countdir(r2dir->newdir, r2dir);
			}
		}
	}
	closedir(dir1);
	r2dir->dir_names[r2dir->arrnum] = NULL;
	return (r2dir->num_dir);
}

int		get_files(char **arreg, char *arg)
{
	struct dirent   *test;
	DIR             *dir1;
	int				i;

	i = 0;
	if ((dir1 = opendir(arg)) == NULL)
		return (0);
	while ((test = readdir(dir1)) != NULL)
	{
		arreg[i] = malloc(20);
		if (test->d_name[0] != '.')
		{
			arreg[i] = test->d_name;
			i++;
		}
	}
	arreg[i + 1] = NULL;
	sort_reg(arreg);
	display_ls(arreg);
	return (i);
}


void	clear_arreg(struct s_dirstuff *r2dir)
{
	int	i;

	i = 0;
	while (r2dir->arreg[i])
	{
		ft_bzero(r2dir->arreg[i], ft_strlen(r2dir->arreg[i]));
		i++;
	}
}

int	ls_r2(char *arg, struct s_dirstuff *r2dir)
{
	DIR             *dir1;
	int				i;

	i = 0;
	get_files(r2dir->arreg, arg);
	countdir(arg, r2dir);
	sort_reg(r2dir->dir_names);
	while (r2dir->dir_names[i])
	{
		if ((dir1 = opendir(r2dir->dir_names[i])) == NULL)
			return (0);
			ft_printf("\n%s\n", r2dir->dir_names[i]);
			clear_arreg(r2dir);
			get_files(r2dir->arreg, r2dir->dir_names[i]);
		i++;
	}
	return (0);
}
