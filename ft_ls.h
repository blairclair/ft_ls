/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 09:05:40 by agrodzin          #+#    #+#             */
/*   Updated: 2018/07/05 12:52:14 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <string.h>
# include <stdio.h>
# include "ft_ls.h"
# include "libft/printf_functions/ft_printf.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

struct	s_dirstuff
{
	char	*newdir;
	int		num_dir;
	char	**arreg;
	char	**dir_names;
	int		arrnum;
	char	r;
	char	r2;
	char	t;
	char	l;
	char	reg;
	char	a;
	char	f;
	char	d;
	char	g;
	char	nt;
};

struct	s_timestuff
{
	char		**regtime;
	char		**nantime;
	char		*realtname;
	char		**tmpregtimei;
	char		**tmpnantimei;
};

struct	s_line_stuff
{
	char		**name;
	char		**perm;
	char		**user;
	char		**group;
	int			*bsize;
	char		**date;
	int			*num;
	int			*size_padding;
	char		*realname;
};

struct	s_sortstuff
{
	char	*namesort;
	char	*permsort;
	char	*usersort;
	char	*groupsort;
	int		bsizesort;
	char	*datesort;
	int		numsort;
};

int		ls_r(char *arg);
int		ls_reg(char *arg);
int		ls_r2(char *arg, struct s_dirstuff *r2dir);
int		get_num_reg(char *arg);
char	**sort_reg(char **arreg);
void	display_ls(char **arreg);
char	*ft_strcmp_ls(char *ss1, char *ss2);
int		countdir(char *arg, struct s_dirstuff *r2dir);
int		ls_a(char *arg);
int		ls_ti(char *arg, struct s_timestuff *ts);
int		conv_month2(int i, int arr_track, char *newdate,
					struct s_timestuff *ts);
int		conv_month(int i, int arr_track, char *newdate,
					struct s_timestuff *ts);
int		conv_day_num(int i, int arr_track, char *newdate,
					struct s_timestuff *ts);
char	**conv_full_date(char *arg, struct s_timestuff *ts);
char	*ft_strcmp_ls_i(char *ss1, char *ss2);
int		get_num_date(char *arg);
int		ls_l(char *arg, struct s_line_stuff *lstuff);
int		ls_f(char *arg);
int		ls_d(char	*arg);
void	user_perm(char *perm, struct stat statcheck);
void	group_perm(char *perm, struct stat statcheck);
void	other_perm(char *perm, struct stat statcheck);
char	*get_perm(char *perm, struct stat statcheck);
int		get_num(struct stat statcheck);
char	*get_user(struct stat statcheck);
char	*get_group(struct stat statcheck);
int		get_file_size(struct stat statcheck);
char	*get_date(char *date, struct stat statcheck);
char	**get_arr(char *arg, struct s_line_stuff *lstuff);
char	**sort_line(char **arreg, struct s_line_stuff *lstuff);
int		sort_size(int *bsize);
int		ls_g(char *arg, struct s_line_stuff *lstuff);
char	*ft_ltoa_ls(long long n);
void	free_l(struct s_line_stuff *lstuff);
int		get_reg_arr(char **arreg, struct dirent *test, int i);
char	*get_padding(char *padding, int padnum,
					int i, struct s_line_stuff *lstuff);

#endif
