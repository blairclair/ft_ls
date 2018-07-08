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

long	ft_atol(const char *str)
{
	int		i;
	long	num;
	int		check;

	i = 0;
	num = 0;
	check = 1;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\r' ||
		str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		check = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num * check);
}

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

int		sort_time2(char **arrtime, char **arreg, int j, struct s_timestuff *ts)
{
	int		first;
	int		second;

	first = ft_atoi(ts->nantime[j + 1]);
	second = ft_atoi(ts->nantime[j]);

	if (second < first)
	{
		arrtime[j + 1] = arrtime[j];
		arreg[j + 1] = arreg[j];
		ts->nantime[j + 1] = ts->nantime[j];
	}
	return (j);
}

void    swap_char(char **x, char **y)
{
    char *tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

char	**sort_time(char **arreg, char **arrtime, struct s_timestuff *ts)
{
	int	n;
	int	i;
	int	j;

	i = 0;
	j = 0;
	n = 0;
	while (arreg[n])
		n++;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_atol(arrtime[j]) < ft_atol(arrtime[j + 1]))
			{
				swap_char(&arreg[j], &arreg[j + 1]);
				swap_char(&arrtime[j], &arrtime[j + 1]);
				swap_char(&ts->nantime[j], &ts->nantime[j + 1]);
			}
			else if (ft_atol(arrtime[j]) == ft_atol(arrtime[j + 1]))
			{
				if (ft_atol(ts->nantime[j]) < ft_atol(ts->nantime[j + 1]))
				{
					swap_char(&arreg[j], &arreg[j + 1]);
					swap_char(&arrtime[j], &arrtime[j + 1]);
					swap_char(&ts->nantime[j], &ts->nantime[j + 1]);
				}
			}
			j++;
		}
		i++;
	}
	return (arreg);
}
