/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:02:29 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/12 10:13:47 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



//DONT FORGET TO OPTIMIZE THIS IS RIDICULOUS
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include "ft_ls.h"
#include "libft/printf_functions/ft_printf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <sys/xattr.h>

char  *parse_args2(char *arg_list)
{
    int i;
    char    *path;

    i = 0;
    while (arg_list[i])
    {
        if (arg_list[i] == '-' && (arg_list[i + 1] == 'R' ||
         arg_list[i + 1] == 'a' || arg_list[i + 1] == 'r' || arg_list[i + 1] == 't'
         || arg_list[i + 1] == 'l'))
            break ;
        i++;
    }
    if (ft_strlen(arg_list) > 3 && i != (int)ft_strlen(arg_list))
    {
        path = malloc(ft_strlen(arg_list) - i);
        ft_memmove(path, arg_list + (i + 2), ft_strlen(arg_list) - (i + 2));
    }
    else
    {
        path = malloc(1);
        ft_strcpy(path, ".");
    }
    return (path);
}  

void    parse_args(char *arg_list, struct s_dirstuff *lsdirs, struct timestuff *ts, struct line_stuff *lstuff)
{
    int i;
    char    *path;
    i = 0;
    lsdirs->arreg = malloc(sizeof(lsdirs->arreg) * get_num_reg(".") + 1);
    path = parse_args2(arg_list);
    while (arg_list[i])
    {
        if (arg_list[i] == '-')
        {
            i++;
            if (arg_list[i] == '1')
                i++;
            if (arg_list[i] == 'R')
                ls_r2(path, lsdirs);
            else if (arg_list[i] == 'a')
                ls_a(path);
            else if (arg_list[i] == 'r')
                ls_r(path);
            else if (arg_list[i] == 't')
                ls_ti(path, ts);
            else if (arg_list[i] == 'l')
                ls_l(path, lstuff);
           // if (ft_strlen(arg_list) > 3)
           //     parse_args2(arg_list, lsdirs, ts, lstuff);
        }
        i++;
    }
}

int     main(int argc, char *argv[])
{  
    struct s_dirstuff lsdirs;
    struct timestuff ts;
    int     i;
    char    *arg_list;
    struct line_stuff lstuff;
 
    arg_list = "";
    i = 3;
    ts.nantime = NULL;
    lsdirs.newdir = NULL;
    lsdirs.num_dir = 0;
    lsdirs.arrnum = 0;
    lsdirs.dir_names = malloc(200);
    lstuff.name = NULL;
     arg_list = ft_strjoin(arg_list, argv[1]);
  
    if (argc == 1 || !ft_strcmp(arg_list, "-1"))
    {    
        ls_reg(".");
    }
      else
    {
        while (i < argc + 1)
        {
            ft_strcat(arg_list, argv[i - 1]);  
            i++;
        }
       parse_args(arg_list, &lsdirs, &ts, &lstuff);
    }
 //   ls_r2(".", &lsdirs);*/
    free(lsdirs.dir_names);
    free(lsdirs.arreg);
    return (0);
}
