/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemarch <elemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 12:58:01 by elemarch          #+#    #+#             */
/*   Updated: 2015/06/01 12:58:05 by elemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#include "../ft_sh1.h"

char	*sh_getenv_val(t_en *en, const char *str)
{
	int		id;
	int		i;
	char	*val;

	i = 0;
	id = sh_getenv(en, str);
	if (id == -1)
		return ("{NULL}");
	while (en->env[id][i] != '=')
		i++;
	i++;
	val = ft_strdup(&(en->env[id][i]));
	return (ft_strtrim(val));
}

int		sh_getenv(t_en *en, const char *str)
{
	int		i;
	int		j;

	i = 0;
	while (en->env && en->env[i])
	{
		j = 0;
		while (en->env[i][j] && str[j])
		{
			if (en->env[i][j] != str[j])
				break ;
			j++;
		}
		if (str[j] == '\0' && en->env[i][j] == '=')
			return (i);
		i++;
	}
	return (-1);
}
