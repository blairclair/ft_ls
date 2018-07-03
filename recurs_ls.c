/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 09:03:24 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/26 14:08:48 by agrodzin         ###   ########.fr       */
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

char	*ft_strjoin3(char *s1, char *s2)
{
	char	*s3;
	int		i;
	
	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	else
	{
		s3 = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (s3 == NULL)
			return (NULL);
		ft_strcpy(s3, s1);
		ft_strcat(s3, s2);
		while (s3[i])
			i++;
		s3[i] = '\0';
	}
	free(s1);
	return (s3);
}


int		countdir(char *arg, struct s_dirstuff *r2dir)
{
	struct dirent   *test;
	DIR             *dir1;
	struct stat     statcheck;
	r2dir->newdir = malloc(200);
	if ((dir1 = opendir(arg)) == NULL)
	    return (r2dir->num_dir);
	while ((test = readdir(dir1)) != NULL)
	{
		if (test->d_name[0] != '.')
		{
			
			ft_bzero(r2dir->newdir, ft_strlen(r2dir->newdir));
			r2dir->newdir = ft_strcat(r2dir->newdir, arg);
			r2dir->newdir = ft_strcat(r2dir->newdir, "/");
			r2dir->newdir = ft_strcat(r2dir->newdir, test->d_name);
			stat(r2dir->newdir, &statcheck);
			if (S_ISDIR(statcheck.st_mode))//checks if isdirectory
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
	struct dirent   *test;
	DIR             *dir1;
	int				i;

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

void	free_r2(struct s_dirstuff *r2dir)
{
	int	j;

	j = 0;
	free(r2dir->newdir);
	while (r2dir->dir_names[j])
	{
		free(r2dir->dir_names[j]);
		j++;
	}
	j = 0;

}
int	ls_r2(char *arg, struct s_dirstuff *r2dir)
{
	DIR             *dir1;
	int				i;
	int				j;

	j = 0;
	i = 0;
	if (!get_files(r2dir, arg))
		return (0);
	countdir(arg, r2dir);
	sort_reg(r2dir->dir_names);
	while (r2dir->dir_names[i])
	{
		if ((dir1 = opendir(r2dir->dir_names[i])) == NULL)
		{
			ft_printf("ls: %s: no such file or directory\n", arg);
			return (0);
		}
		ft_printf("\n%s\n", r2dir->dir_names[i]);
		clear_arreg(r2dir);
		get_files(r2dir, r2dir->dir_names[i]);
		i++;
	}
	closedir(dir1);
	free_r2(r2dir);
	return (0);
}
