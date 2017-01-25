/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemarch <elemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 12:57:55 by elemarch          #+#    #+#             */
/*   Updated: 2015/06/01 12:57:57 by elemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#include "../ft_sh1.h"

void	sh_split_epur(t_en *en)
{
	int i;
	int	j;

	i = 0;
	while (en->arg[i])
	{
		j = 0;
		while (en->arg[i][j])
		{
			if (en->arg[i][j] == 127 || en->arg[i][j] == '\"')
				en->arg[i][j] = ' ';
			j++;
		}
		en->arg[i] = ft_strtrim(en->arg[i]);
		i++;
	}
}

int		sh_split_skip(t_en *en, int i)
{
	while (en->com[i] && en->com[i] != '\"')
		i++;
	if (!en->com[i])
	{
		sh_error(en, 5);
		return -1;
	}
	return (i);
}

void	sh_split_step1(t_en *en)
{
	int i;

	i = 0;
	while (en->com[i])
	{
		if (en->com[i] == '\t' || en->com[i] == ' ')
			en->com[i] = 127;
		i++;
	}
}

int		sh_split(t_en *en)
{
	int		i;

	en->com = ft_strccat(en->com, " ");
	sh_split_step1(en);
	i = 0;
	while (en->com[i])
	{
		if (en->com[i] == '\"')
		{
			i = sh_split_skip(en, i + 1);
			if (i == -1)
				return (0);
		}
		else if (en->com[i] == 127)
			en->com[i] = ' ';
		i++;
	}
	en->arg = ft_strsplit(en->com, ' ');
	i = 0;
	while (en->com && en->com[i])
	{
		if (en->com[i] == ' ')
		{
			en->com[i] = '\0';
			break ;
		}
		i++;
	}
	sh_split_epur(en);
	return (1);
}
