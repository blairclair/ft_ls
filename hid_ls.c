/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hid_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 13:42:08 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/16 13:42:10 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include "libft/printf_functions/ft_printf.h"
#include "ft_ls.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

char    **sort_back(char **arreg)
{
    int     i;
    int     j;
    char    *x;

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

int ls_r(char *arg)
{
    struct dirent   *test;
    DIR             *dir1;
    char            **arreg;
    int             i;
  
    if ((arreg = malloc(sizeof(arreg) * get_num_reg(arg) + 1)) == NULL)
        return (0);
    i = 0;
    if ((dir1 = opendir(arg)) == NULL)
        return (0);
    while ((test = readdir(dir1)) != NULL )
	{
            if (test->d_name[0] != '.')
			{
                arreg[i] = test->d_name;
                i++;
            }
    }
    arreg[i] = NULL;
    sort_back(arreg);
    display_ls(arreg);
    free(arreg);
    return (0);
}

int ls_a(char *arg)
{
    struct dirent   *test;
    DIR             *dir1;
    char            **arreg;
    int             i;

    if ((arreg = malloc(sizeof(arreg) * get_num_reg(arg) + 1)) == NULL)
        return (0);
    i = 0;
    if ((dir1 = opendir(arg)) == NULL)
        return (0);
    while ((test = readdir(dir1)) != NULL )
	{
        arreg[i] = test->d_name;
        i++;
    }
    arreg[i] = NULL;
    sort_reg(arreg);
    display_ls(arreg);
    free(arreg);
    return (0);
}
