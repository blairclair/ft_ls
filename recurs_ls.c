/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 09:03:24 by agrodzin          #+#    #+#             */
/*   Updated: 2018/07/06 09:35:55 by agrodzin         ###   ########.fr       */
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

void	get_dir_name(struct s_dirstuff *r2dir, struct dirent *test, char *arg)
{
	ft_bzero(r2dir->newdir, ft_strlen(r2dir->newdir));
	r2dir->newdir = ft_strcat(r2dir->newdir, arg);
	r2dir->newdir = ft_strcat(r2dir->newdir, "/");
	r2dir->newdir = ft_strcat(r2dir->newdir, test->d_name);
}

int		countdir(char *arg, struct s_dirstuff *r2dir)
{
	struct dirent	*test;
	DIR				*dir1;
	struct stat		statcheck;

	r2dir->newdir = malloc(200);
	if ((dir1 = opendir(arg)) == NULL)
		return (r2dir->num_dir);
	while ((test = readdir(dir1)) != NULL)
	{
		if (test->d_name[0] != '.')
		{
			get_dir_name(r2dir, test, arg);
			stat(r2dir->newdir, &statcheck);
			if (S_ISDIR(statcheck.st_mode))
			{
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

int		get_files(struct s_dirstuff *r2dir, char *arg)
{
	struct dirent	*test;
	DIR				*dir1;
	int				i;

	i = 0;
	if ((dir1 = opendir(arg)) == NULL)
	{
		no_perm(arg);
		return (0);
	}
	while ((test = readdir(dir1)) != NULL)
	{
		if (test->d_name[0] != '.')
		{
			r2dir->arreg[i] = test->d_name;
			i++;
		}
	}
	r2dir->arreg[i + 1] = NULL;
	sort_reg(r2dir->arreg);
	display_ls(r2dir->arreg);
	closedir(dir1);
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

int		ls_r2(char *arg, struct s_dirstuff *r2dir)
{
	DIR				*dir1;
	int				i;

	i = 0;
	r2dir->arreg = malloc(sizeof(r2dir->arreg) * get_num_reg(arg) + 1);
	if (!get_files(r2dir, arg))
		return (0);
	countdir(arg, r2dir);
	sort_reg(r2dir->dir_names);
	while (r2dir->dir_names[i])
	{
		if ((dir1 = opendir(r2dir->dir_names[i])) == NULL)
		{
			no_perm(arg);
			return (0);
		}
		ft_printf("\n%s:\n", r2dir->dir_names[i]);
		clear_arreg(r2dir);
		get_files(r2dir, r2dir->dir_names[i]);
		i++;
	}
	closedir(dir1);
	free_r2(r2dir);
	return (0);
}
