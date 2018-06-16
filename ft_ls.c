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

#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include "ft_ls.h"
#include "libft/printf_functions/ft_printf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int     main(int argc, char *argv[])
{  
    struct s_dirstuff lsdirs;
    
    lsdirs.newdir = NULL;
    lsdirs.num_dir = 0;
    lsdirs.arrnum = 0;
    lsdirs.dir_names = malloc(200);
    if (argc == 1)
    { 
   //    ls_reg(".");
   
   lsdirs.arreg = malloc(sizeof(lsdirs.arreg) * get_num_reg(".") + 1);
        ls_r2(".", &lsdirs);
    }
    else
    {
     //   ls_reg(argv[1]);
    // lsdirs.dir_names = malloc(countdir(argv[1], &lsdirs));
     lsdirs.arreg = malloc(sizeof(lsdirs.arreg) * get_num_reg(argv[1]) + 20);
        ls_r2(argv[1], &lsdirs);
    }
    return (0);
}
