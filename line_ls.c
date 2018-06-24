/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 18:37:09 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/23 18:37:16 by agrodzin         ###   ########.fr       */
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

void    user_perm(char *perm, struct stat statcheck)
{
     if (statcheck.st_mode & S_IRUSR)
        perm[1] = 'r';
    else
        perm[1] = '-';
    if (statcheck.st_mode & S_IWUSR)
        perm[2] = 'w';
    else 
        perm[2] = '-';
    if (statcheck.st_mode & S_IXUSR)
        perm[3] = 'x';
    else
        perm[3] = '-';
}

void    group_perm(char *perm, struct stat statcheck)
{
    if (statcheck.st_mode & S_IRGRP)
        perm[4] = 'r';
    else
        perm[4] = '-';
    if (statcheck.st_mode & S_IWGRP)
        perm[5] = 'w';
    else
        perm[5] = '-';
    if (statcheck.st_mode & S_IXGRP)
        perm[6] = 'x';
    else
        perm[6] = '-';
}

void    other_perm(char *perm, struct stat statcheck)
{
    if (statcheck.st_mode & S_IROTH)
        perm[7] = 'r';
    else
        perm[7] = '-';
    if (statcheck.st_mode & S_IWOTH)
        perm[8] = 'w';
    else
        perm[8] = '-';
    if (statcheck.st_mode & S_IXOTH)
        perm[9] = 'x';
    else
        perm[9] = '-';
}

char    *get_perm(char *perm, struct stat statcheck)
{
    if (S_ISDIR(statcheck.st_mode))
        perm[0] = 'd';
    else
        perm[0] = '-'; 
    user_perm(&*perm, statcheck);
    group_perm(&*perm, statcheck);
    other_perm(&*perm, statcheck);
    return (perm);
}

int     get_num(struct stat statcheck)
{
    int numlink;

    numlink = statcheck.st_nlink;
    return (numlink);
}

char    *get_user(struct stat statcheck)
{
    struct  passwd *pwd;
    unsigned int    iduser;
    
    iduser = statcheck.st_uid;
    pwd = getpwuid(iduser);
    return (pwd->pw_name);
}

char    *get_group(struct stat statcheck)
{
    struct  group *grp;
    unsigned int    idgroup;
    
    idgroup = statcheck.st_gid;
    grp = getgrgid(idgroup);
    return (grp->gr_name);
}

int     get_file_size(struct stat statcheck)
{
    int     bsize;

    bsize = statcheck.st_size;
    return (bsize);
}

char    *get_date(char *date, struct stat statcheck)
{
    int     i;
    char    *date2;
    int     j;

    j = 0;
    i = 4;
    date2 = malloc(18);
    date = ft_strdup(ctime(&statcheck.st_mtime));
    while (i < 19)
    {
        date2[j] = date[i];
        j++;
        i++;
    }
    return (date2);
}


char    **get_arr(char *arg, struct line_stuff *lstuff)
{
    struct dirent   *test;
    DIR             *dir1;
    char            **arreg;
    int             i;
    struct stat statcheck;

    arreg = malloc(sizeof(arreg) * get_num_reg(arg) + 1);
    lstuff->perm = malloc(sizeof(lstuff->perm) * get_num_reg(arg) + 1);
    lstuff->user = malloc(sizeof(lstuff->name) * get_num_reg(arg) + 1);
    lstuff->group = malloc(sizeof(lstuff->group) * get_num_reg(arg) + 1);
    lstuff->date = malloc(sizeof(char *) *(get_num_date(arg) * 24) + 1);
    lstuff->num = malloc(get_num_date(arg) * sizeof(int));
    lstuff->bsize = malloc((get_num_date(arg) * sizeof(int)) * 7);
    i = 0;
    if ((dir1 = opendir(arg)) == NULL)
        return (0);
    while ((test = readdir(dir1)) != NULL )
	{
            if (test->d_name[0] != '.')
			{
                stat(test->d_name, &statcheck);
                lstuff->perm[i] = malloc(10);
                lstuff->date[i] = malloc(20);
                arreg[i] = test->d_name;
                lstuff->perm[i] = get_perm(lstuff->perm[i], statcheck);
                lstuff->user[i] = get_user(statcheck);
                lstuff->group[i] = get_group(statcheck);
                lstuff->date[i] = get_date(lstuff->date[i], statcheck);
                lstuff->num[i] = get_num(statcheck);
                lstuff->bsize[i] = get_file_size(statcheck);
           //     lstuff->bsize[i] = get_file_size(statcheck);
                i++;
            }
    }
    arreg[i] = NULL;
    lstuff->perm[i] = NULL;
    lstuff->user[i] = NULL;
    lstuff->group[i] = NULL;
    lstuff->date[i] = NULL;
    free(lstuff->perm);
    free(lstuff->user);
    free(lstuff->group);
    free(lstuff->date);
    free(lstuff->num);
    free(lstuff->bsize);
    return (arreg);
}



int ls_l(char *arg, struct line_stuff *lstuff)
{
   int  i;

   i = 0;
   lstuff->name = get_arr(arg, lstuff);
    while (lstuff->name[i])
    {
        ft_printf("%s %d %s %s %d %s %s\n", lstuff->perm[i], lstuff->num[i], lstuff->user[i],
            lstuff->group[i], lstuff->bsize[i], lstuff->date[i], lstuff->name[i]);
        i++;
    } 
   return (0);
}
