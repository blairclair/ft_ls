/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ststrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:47:31 by agrodzin          #+#    #+#             */
/*   Updated: 2018/03/21 19:31:31 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		n_sws(char ws)
{
	int	j;

	j = 0;
	if (ws != ' ' && ws != ',' && ws != '\n' && ws != '\t')
	{
		j = 1;
	}
	else if (ws == '\0')
		j = 0;
	else
		j = 0;
	return (j);
}

static int		is_poss(char const *c, int i)
{
	int	count;

	count = 0;
	while (c[i])
	{
		if (n_sws(c[i]) == 1)
		{
			count = 1;
			break ;
		}
		i++;
	}
	return (count);
}

static char		*get_sws(const char *s, char *sws, int i, int check)
{
	i = 0;
	if ((sws = (char*)malloc((ft_strlen(s) / 2 - check))) == NULL)
		return (NULL);
	while (s[i])
	{
		if (n_sws(s[i]) == 1)
			sws[check++] = s[i++];
		else if (n_sws(s[i]) == 0 && n_sws(s[i - 1]) == 1 && i != 0)
		{
			if (is_poss(s, i) == 1)
			{
				while (n_sws(s[i]) == 0)
					sws[check++] = s[i++];
			}
			else
			{
				sws[check] = '\0';
				break ;
			}
		}
		else if (n_sws(s[i]) == 0)
			i++;
	}
	sws[check] = '\0';
	return (sws);
}

char			*ft_strtrim(char const *s)
{
	int		i;
	char	*sws;
	int		check;

	check = 0;
	if (s == NULL || (sws = (char*)malloc((ft_strlen(s) / 2 - check))) == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (n_sws(s[i]) == 0 && n_sws(s[i - 1]) == 1 && i != 0)
		{
			if (is_poss(s, i) == 1)
			{
				while (n_sws(s[i]) == 0)
					i++;
			}
		}
		else if (n_sws(s[i]) == 0)
			check++;
		i++;
	}
	check = 0;
	sws = get_sws(s, sws, i, check);
	return (sws);
}
