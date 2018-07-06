/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 08:48:45 by agrodzin          #+#    #+#             */
/*   Updated: 2018/07/06 08:48:48 by agrodzin         ###   ########.fr       */
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

char	**sort_back(char **arreg)
{
	int		i;
	int		j;
	char	*x;

	j = 0;
	i = 1;
	while (arreg[i])
	{
		x = arreg[i];
		j = i - 1;
		while (j >= 0 && ft_strcmp_ls(arreg[j], x) == arreg[j])
		{
			arreg[j + 1] = arreg[j];
			j--;
		}
		arreg[j + 1] = x;
		i++;
	}
	return (arreg);
}

char	**sort_reg(char **arreg)
{
	int		i;
	int		j;
	char	*x;

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
