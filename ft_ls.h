/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 09:05:40 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/09 09:05:43 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include "ft_ls.h"
#include "libft/printf_functions/ft_printf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct s_dirstuff{
    char    *newdir;
    int     num_dir;
    char    **arreg;
    char    **dir_names;
    int     arrnum;
                };

struct timestuff{
    char      **regtime;
    long long *nantime;

};

struct line_stuff{
    char        **name;
    char        **perm;
    char        **user;
    char        **group;
    int         *bsize;
    char        **date;
    int         *num;
};

int     ls_r(char *arg);
int     ls_reg(char *arg);
int     ls_r2(char *arg, struct s_dirstuff *r2dir);
int     get_num_reg(char *arg);
char    **sort_reg(char **arreg);
void    display_ls(char **arreg);
char	*ft_strcmp_ls(char *ss1, char *ss2);
int		countdir(char *arg, struct s_dirstuff *r2dir);
int     ls_a(char *arg);
int     ls_ti(char *arg, struct timestuff *ts);
int     conv_month2(int i, int arr_track, char *newdate, struct timestuff *ts);
int     conv_month(int i, int arr_track,  char *newdate, struct timestuff *ts);
int     conv_day_num(int i, int arr_track, char *newdate, struct timestuff *ts);
char    **conv_full_date(struct timestuff *ts);
char    *ft_strcmp_ls_i(char *ss1, char *ss2);
int     get_num_date(char *arg);
int ls_l(char *arg, struct line_stuff *lstuff);

#endif