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
    display_ls(arreg);
  /*  i = 0;
    while (arreg[i])
    {
        ft_printf("%s %s\n\n", arreg[i], arrtime[i]);
        i++;
    }*/
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
    char             **date_num;

    arreg = malloc(sizeof(char *) * get_num_reg(arg) + 1);
    ts->nantime = malloc(sizeof(long) * (get_num_date(arg) * 7) + 1);
    ts->regtime = malloc(sizeof(char *) *(get_num_date(arg) * 24) + 1); 
    i = 0;
    if ((dir1 = opendir(arg)) == NULL)
        return (0);
    while ((test = readdir(dir1)) != NULL)
	{
        if (test->d_name[0] != '.')
		{
            arreg[i] = malloc(ft_strlen(test->d_name) + 1);
            arreg[i] = test->d_name;
            arreg[i][ft_strlen(test->d_name) + 1] = '\0';
            lstat(test->d_name, &statcheck);
            ts->regtime[i] = ft_strdup(ctime(&statcheck.st_mtime));
            ti = statcheck.st_mtimespec.tv_nsec;
            ts->nantime[i] = ti;
            i++;
        }
    }
   // ft_printf("rtime: %s", ts->regtime[0]);
    arreg[i] = NULL;
    ts->regtime[i] = NULL;
    ts->nantime[i] = '\0';
   // display_ls(ts->regtime);
    date_num = conv_full_date(ts);
    i = 0;
    sort_time(arreg, date_num);
    free(arreg);
    free(ts->nantime);
    free(ts->regtime);
    return (0);
}