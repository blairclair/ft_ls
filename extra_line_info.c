/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_line_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 09:10:35 by agrodzin          #+#    #+#             */
/*   Updated: 2018/07/06 09:10:38 by agrodzin         ###   ########.fr       */
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

int		get_num(struct stat statcheck)
{
	int numlink;

	numlink = statcheck.st_nlink;
	return (numlink);
}

char	*get_user(struct stat statcheck)
{
	struct passwd	*pwd;
	unsigned int	iduser;
	char			*pwname2;

	iduser = statcheck.st_uid;
	pwd = getpwuid(iduser);
	pwname2 = pwd->pw_name;
	pwname2[ft_strlen(pwd->pw_name) + 1] = '\0';
	return (pwname2);
}

char	*get_group(struct stat statcheck)
{
	struct group	*grp;
	unsigned int	idgroup;
	char			*strgrp;

	idgroup = statcheck.st_gid;
	grp = getgrgid(idgroup);
	strgrp = grp->gr_name;
	strgrp[ft_strlen(grp->gr_name) + 1] = '\0';
	return (strgrp);
}

int		get_file_size(struct stat statcheck)
{
	int	bsize;

	bsize = statcheck.st_size;
	return (bsize);
}

char	*get_date(char *date, struct stat statcheck)
{
	int		i;
	char	*date2;
	int		j;

	j = 0;
	i = 4;
	date2 = malloc(18);
	date = ft_strdup(ctime(&statcheck.st_mtime));
	while (i < 16)
	{
		date2[j] = date[i];
		j++;
		i++;
	}
	date2[j] = '\0';
	free(date);
	return (date2);
}
