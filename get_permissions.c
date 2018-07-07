/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_permissions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 09:07:58 by agrodzin          #+#    #+#             */
/*   Updated: 2018/07/06 09:08:01 by agrodzin         ###   ########.fr       */
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

void	user_perm(char *perm, struct stat statcheck)
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

void	group_perm(char *perm, struct stat statcheck)
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

void	other_perm(char *perm, struct stat statcheck)
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
	perm[10] = '\0';
}

char	*get_perm(char *perm, struct stat statcheck)
{
	if (S_ISDIR(statcheck.st_mode))
		perm[0] = 'd';
	else if (S_ISBLK(statcheck.st_mode))
		perm[0] = 'b';
	else if (S_ISCHR(statcheck.st_mode))
		perm[0] = 'c';
	else if (S_ISLNK(statcheck.st_mode))
		perm[0] = 'l';
	else if (S_ISSOCK(statcheck.st_mode))
		perm[0] = 's';
	else if (S_ISFIFO(statcheck.st_mode))
		perm[0] = 'p';
	else
		perm[0] = '-';
	user_perm(&*perm, statcheck);
	group_perm(&*perm, statcheck);
	other_perm(&*perm, statcheck);
	return (perm);
}
