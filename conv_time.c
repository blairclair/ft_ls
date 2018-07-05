/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 08:05:07 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/26 14:06:44 by agrodzin         ###   ########.fr       */
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

int     conv_month2(int i, int arr_track, char *newdate, struct s_timestuff *ts)
{
	int j;

	j = 0;
	while (ts->regtime[i][j] != ' ')
		j++;
	if (ts->regtime[i][j + 1] == 'A' && ts->regtime[i][j + 2] == 'u')
		newdate[arr_track] = '8';
	else if (ts->regtime[i][j + 1] == 'S')
		newdate[arr_track] = '9';
	else if (ts->regtime[i][j + 1] == 'O')
	{
		newdate[arr_track] = '1';
		arr_track++;
		newdate[arr_track] = '0';
	}
	else if (ts->regtime[i][j + 1] == 'N')
	{
		newdate[arr_track] = '1';
		arr_track++;
		newdate[arr_track] = '1';
	}
	else if (ts->regtime[i][j + 1] == 'D')
	{
		newdate[arr_track] = '1';
		arr_track++;
		newdate[arr_track] = '2';
	}
	else
		return (0);
	return (arr_track);
}

int     conv_month(int i, int arr_track,  char *newdate, struct s_timestuff *ts)
{
	int j;

	j = 0;
	while (ts->regtime[i][j] != ' ')
		j++;
	if (ts->regtime[i][j + 1] == 'J' && ts->regtime[i][j + 2] == 'a')
		newdate[arr_track] = '1';
	else if (ts->regtime[i][j + 1] == 'F')
		newdate[arr_track] = '2';
	else if (ts->regtime[i][j + 1] == 'M' && ts->regtime[i][j + 2] == 'a' 
			&& ts->regtime[i][j + 3] == 'r')
		newdate[arr_track] = '3';
	else if (ts->regtime[i][j + 1] == 'A' && ts->regtime[i][j + 2] == 'p')
		newdate[arr_track] = '4';
	else if (ts->regtime[i][j + 1] == 'M' && ts->regtime[i][j + 2] == 'a' 
			&& ts->regtime[i][j + 3] == 'y')
		newdate[arr_track] = '5';
	else if (ts->regtime[i][j + 1] == 'J' && ts->regtime[i][j + 2] == 'u' 
			&& ts->regtime[i][j + 3] == 'n')
		newdate[arr_track] = '6';
	else if (ts->regtime[i][j + 1] == 'J' && ts->regtime[i][j + 2] == 'u' 
			&& ts->regtime[i][j + 3] == 'l')
		newdate[arr_track] = '7';
	if (conv_month2(i, arr_track, newdate, ts)!= 0)
		arr_track = conv_month2(1, arr_track, &*newdate, ts);
//	arr_track++;
//	newdate[arr_track] = '/';
	return (arr_track);
}

int     conv_day_num(int i, int arr_track, char *newdate, struct s_timestuff *ts)
{
	int j;
	int track;

	j = 0;
	track = 0;
	while (!ft_isdigit(ts->regtime[i][j]))
		j++;
	arr_track++;
	while ((ts->regtime[i][j]) != ' ')
	{
		j++;
		track++;
	}
	j-= track;
	if (track == 1)
	{
		newdate[arr_track] = '0';
		arr_track++;
	}
	while (ts->regtime[i][j] != ' ')
	{
		newdate[arr_track] = ts->regtime[i][j];
		arr_track++;
		j++;
	}
//	newdate[arr_track] = '/';
	arr_track--;
	return (arr_track);
}

int conv_year(int i, int arr_track, char *newdate, struct s_timestuff *ts)
{
	int col;
	int j;

	col = 0;
	j = 0;
	arr_track++;
	while (col < 2)
	{
		if (ts->regtime[i][j] == ':')
			col++;  
		j++;
	}
	j += 3;
	while (ts->regtime[i][j])
	{
		newdate[arr_track] = ts->regtime[i][j];
		arr_track++;
		j++;
	}
	arr_track--;
	return (arr_track);
}

int     conv_time_day(int i, int arr_track, char *newdate, struct s_timestuff *ts)
{
	int		j;

	j = 0;
	while (!ft_isdigit(ts->regtime[i][j]))
		j++;
	while (ts->regtime[i][j] != ' ')
		j++;
	j++;
	while (ts->regtime[i][j] != ' ')
	{
		if (ts->regtime[i][j] == ':')
			j++;
		else
		{
			newdate[arr_track] = ts->regtime[i][j];
			arr_track++;
			j++;
		}
	}
	
	

	j = 0;
	while (ts->nantime[i][j])
	{
		newdate[arr_track] = ts->nantime[i][j];
		j++;
		arr_track++;
	}
	newdate[arr_track] = '\0';
	//ft_strcat(newdate, ts->nantime[i]);
	//printf("%s\n", newdate);

	return (arr_track);
}

char **conv_full_date(char *arg, struct s_timestuff *ts)
{
	int     i;
	char    **newdate;
	int     arr_track;

	i = 0;
	arr_track = 0;
	newdate = malloc(sizeof(char**) * (get_num_date(arg) * 27 + 1));
	while (ts->regtime[i])
	{    
		newdate[i] = malloc(28);
		arr_track = conv_month(i, arr_track, &*newdate[i], ts);
		arr_track = conv_day_num(i, arr_track, &*newdate[i], ts);
		arr_track = conv_year(i, arr_track, &*newdate[i], ts);
		arr_track = conv_time_day(i, arr_track, &*newdate[i], ts);
		arr_track = 0;
		i++;
	}
	newdate[i] = NULL;
	return (newdate);
}
