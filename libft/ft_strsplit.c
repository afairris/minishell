/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemarch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 11:38:51 by elemarch          #+#    #+#             */
/*   Updated: 2015/01/06 17:52:06 by elemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		get_wcount(char *s, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	while (*s == c)
		s++;
	while (*s)
	{
		if (*s == c)
			j = 0;
		else
		{
			if (j == 0)
			{
				i++;
				j = 1;
			}
		}
		s++;
	}
	return (i);
}

static char		*ft_strsplit_wd(char *s, int start, int end)
{
	char	*str;
	int		i;

	i = 0;
	if ((str = ft_strnew(end - start)) == NULL)
		return (NULL);
	while (start < end)
	{
		str[i++] = s[start];
		start++;
	}
	return (str);
}

static int		ft_strsplit_wend(char *s, int pos, char c)
{
	while (s[pos] != c)
	{
		if (s[pos] == '\0')
			break ;
		pos++;
	}
	return (pos);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**arr;
	char	**begin;
	int		wcount;
	int		i;
	int		j;

	i = 0;
	wcount = get_wcount((char *)s, c);
	if ((arr = (char **)malloc(sizeof(char **) * wcount + 1)) == NULL)
		return (NULL);
	begin = arr;
	while (wcount-- > 0)
	{
		while (s[i] == c)
			i++;
		j = ft_strsplit_wend((char *)s, i, c);
		*arr++ = ft_strsplit_wd((char *)s, i, j);
		i = j;
	}
	*arr = 0;
	return (begin);
}

void			ft_strsplit_free(char **arr)
{
	char *str;

	if (!arr || !*arr)
		return ;
	while (arr)
	{
		str = *arr;
		if (str)
			free(str);
		arr++;
	}
}
