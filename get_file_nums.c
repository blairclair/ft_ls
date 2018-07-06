/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_nums.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 08:34:38 by agrodzin          #+#    #+#             */
/*   Updated: 2018/07/06 08:34:40 by agrodzin         ###   ########.fr       */
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

int		get_num_reg(char *arg)
{
	struct dirent	*test;
	DIR				*dir1;
	int				i;

	i = 0;
	if ((dir1 = opendir(arg)) == NULL)
	{
		return (0);
	}
	while ((test = readdir(dir1)) != NULL)
	{
		if (test->d_name[0] != '.')
		{
			i += ft_strlen(test->d_name);
		}
	}
	closedir(dir1);
	return (i);
}

int		get_num_date(char *arg)
{
	struct dirent	*test;
	DIR				*dir1;
	int				i;

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
