/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:33:39 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/16 14:33:40 by agrodzin         ###   ########.fr       */
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

char    **sort_time(char **arreg, char **arrtime)
{
    int     i;
    int     j;
    char    *x;
    char    *x2;

    j = 0;
    i = 1;
   while (arrtime[i])
    {
        x2 = arrtime[i];
        x = arreg[i];
        j = i - 1;
        while (j >= 0 && ft_strcmp_ls(arrtime[j], x2) == arrtime[j])
        {
            arrtime[j + 1] = arrtime[j];
            arreg[j + 1] = arreg[j];
            j--;
        }
        arreg[j + 1] = x;
        arrtime[j + 1] = x2;
        i++;
    }
    return (arreg);
}




int ls_ti(char *arg, struct timestuff *ts) 
{
    struct dirent   *test;
    DIR             *dir1;
    char            **arreg;
    int             i;
    struct stat     statcheck;
    time_t           ti;

    if ((arreg = malloc(sizeof(arreg) * get_num_reg(arg) + 1)) == NULL)
        return (0);
    if ((ts->nantime = malloc(sizeof(ts->nantime) * get_num_reg(arg) + 1)) == NULL)
        return (0);   
    ts->regtime = malloc(sizeof(ts->regtime) * get_num_reg(arg) + 1); 
    i = 0;
    if ((dir1 = opendir(arg)) == NULL)
        return (0);
    while ((test = readdir(dir1)) != NULL)
	{
        if (test->d_name[0] != '.')
		{
            arreg[i] = test->d_name;
            lstat(test->d_name, &statcheck);
            ts->regtime[i] = ft_strdup(ctime(&statcheck.st_mtime));
            ti = statcheck.st_mtimespec.tv_nsec;
            ts->nantime[i] = ti;
            i++;
        }
    }
    arreg[i] = NULL;
    conv_full_date(ts);
    free(arreg);
    free(ts->nantime);
    free(ts->regtime);
    return (0);
}