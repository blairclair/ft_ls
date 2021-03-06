/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reg_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:06:30 by agrodzin          #+#    #+#             */
/*   Updated: 2018/07/05 12:37:16 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include "libft/printf_functions/ft_printf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ft_ls.h"

void	no_perm(char *arg)
{
	struct stat statcheck;

	stat(arg, &statcheck);
	if (!(statcheck.st_mode & S_IRUSR) && S_ISDIR(statcheck.st_mode))
		ft_printf("ls: %s: Permission denied\n", arg);
		else
			ft_printf("ls: %s: no such file or directory\n", arg);
}

char	*ft_strcmp_ls(char *ss1, char *ss2)
{
	char	*temp_s1;
	char	*temp_s2;

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

void	display_ls(char **arreg)
{
	int i;

	i = 0;
	while (arreg[i])
	{
		ft_printf("%s\n", arreg[i]);
		i++;
	}
}

int		get_reg_arr(char **arreg, struct dirent *test, int i)
{
	if (test->d_name[0] != '.')
	{
		arreg[i] = test->d_name;
		i++;
	}
	return (i);
}

int		ls_reg(char *arg)
{
	struct dirent	*test;
	DIR				*dir1;
	char			**arreg;
	int				i;
	
	if ((arreg = malloc(sizeof(arreg) * get_num_reg(arg) + 1)) == NULL)
		return (0);
	i = 0;
	if ((dir1 = opendir(arg)) == NULL)
	{
		no_perm(arg);
		free(arreg);
		return (0);
	}
	while ((test = readdir(dir1)) != NULL)
		i = get_reg_arr(arreg, test, i);
	arreg[i] = NULL;
	sort_reg(arreg);
	display_ls(arreg);
	free(arreg);
	closedir(dir1);
	return (1);
}
