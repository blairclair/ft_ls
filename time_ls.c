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


char    **conv_date(struct timestuff *ts)
{
    char    **newdate;
    int     i;
    int     j;

    j = 0;
    i = 0;
    newdate = malloc(200);
    while (ts->regtime[i])
    {
        if(ts->regtime[i][0] == 'S' && ts->regtime[i][1] == 'u')
            newdate[i][0] = '1';
        else if (ts->regtime[i][0] == 'M')
            newdate[i][0] = '2';
        else if (ts->regtime[i][0] == 'T' && ts->regtime[i][1] == 'u')
            newdate[i][0] = '3';
        else if (ts->regtime[i][0] == 'W')
            newdate[i][0] = '4';
        else if (ts->regtime[i][0] == 'T' && ts->regtime[i][1] == 'h')
            newdate[i][0] = '5';
        else if (ts->regtime[i][0] == 'F')
            newdate[i][0] = '6';
        i++;
    }

}
/*


char    **sort_day(struct timestuff *ts)
{
    int i;
    int j;
    char    **sd2;
    char    **sd_hour;
    int     numhour;
    int     num2;

    num2 = 0;
    sd2 = malloc(200);
    sd_hour = malloc(200);
    i = 0;
    j = 0;
    numhour = 0;
   // printf("%s\n", ts->regtime[i]);
    while (ts->regtime[i])
    {
        j = 0;
        while (!ft_isdigit(ts->regtime[i][j]))
            j++;
        if (ts->regtime[i][j + 1] == ' ')
        {
            //ft_printf("no: %s\n", ts->regtime[i] + j);
            sd_hour[numhour] = ts->regtime[i] + j;
            ft_printf("sdour: %s\n", sd_hour[numhour]);
            numhour++;
        }
        else
        {
          //  printf("%s\n", ts->regtime[i]);
             sd2[num2] = ts->regtime[i] + j;
             num2++;
        }
        i++;
    }
    i = 0;
  
    sd_hour[numhour] = NULL;
    sd2[num2] = NULL;
    
   // sort_reg(sd_hour);
   sort_reg(sd2);
  //display_ls(sd_hour);
   //display_ls(sd2);
    return (ts->regtime);
}
*/
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
    display_ls(ts->regtime);
    //sort_day(ts);
    i = 0;
    while (arreg[i])
    {
  //      ft_printf("%s: %s %ld\n", arreg[i], ts->regtime[i], ts->nantime[i]);
        i++; 
    }
    free(arreg);
    return (0);
}