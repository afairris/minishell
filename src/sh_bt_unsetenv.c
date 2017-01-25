/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_bt_unsetenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemarch <elemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 12:57:55 by elemarch          #+#    #+#             */
/*   Updated: 2015/06/01 12:57:57 by elemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#include "../ft_sh1.h"

void			sh_btue_mod_env(int pos, t_en *en)
{
	int		i;
	int		j;
	char	**nen;

	i = 0;
	j = 0;
	while (en->env[i])
		i++;
	nen = (char**)malloc(sizeof(char*) * i);
	i = 0;
	while (en->env[i])
	{
		if (i != pos)
		{
			nen[j] = ft_strdup(en->env[i]);
			j++;
		}
		i++;
	}
	nen[i] = NULL;
	en->env = nen;
}

void			sh_builtin_unsetenv(t_en *en)
{
	char	*vname;
	int		pos;
	int		i;

	i = 1;
	if (en->arg[1] == NULL)
	{
		ft_putendl("unsetenv: environment variable needed");
		return ;
	}
	while (en->arg[i])
	{
		vname = ft_strdup((const char*)en->arg[i]);
		pos = sh_getenv(en, vname);
		if (pos == -1)
		{
			ft_putstrs("setenv: entry not found: $S\n", vname);
			return ;
		}
		else
			sh_btue_mod_env(pos, en);
		i++;
	}
}
