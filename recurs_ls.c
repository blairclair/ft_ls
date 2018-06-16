/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 09:03:24 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/11 18:25:04 by agrodzin         ###   ########.fr       */
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
				r2dir->num_dir++;
				countdir(r2dir->newdir, r2dir);
			}
		}
	}
	closedir(dir1);
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
	struct dirent   *test;
    DIR             *dir1;
	struct stat     statcheck;

	ft_printf("\n\n\n%s\n\n\n", arg);
   
	clear_arreg(r2dir);
    if ((dir1 = opendir(arg)) == NULL)
        return (0);
	 get_files(r2dir->arreg, arg);
//	 display_ls(r2dir->arreg);
    while ((test = readdir(dir1)) != NULL)
	{		
		if (test->d_name[0] != '.')
			{
				r2dir->newdir = ft_strjoin(arg, "/");
				r2dir->newdir = ft_strjoin(r2dir->newdir, test->d_name);
               	stat(r2dir->newdir, &statcheck);
				 if (S_ISDIR(statcheck.st_mode))//checks if isdirectory
            	{
                	ls_r2(r2dir->newdir, r2dir);
            	}

            }
    }

	return (0);
}
