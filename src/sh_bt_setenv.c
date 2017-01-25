/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_bt_setenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemarch <elemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 12:57:55 by elemarch          #+#    #+#             */
/*   Updated: 2015/06/01 12:57:57 by elemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../ft_sh1.h"

#define CREATE_ENTRY sh_btse_create_entry(en->arg[i], en->arg[i + 1])

void		sh_btse_add_env(char *val, t_en *en)
{
	int		i;
	char	**nen;

	i = 0;
	while (en->env[i])
		i++;
	nen = (char**)malloc(sizeof(char*) * i + 2);
	i = 0;
	while (en->env[i])
	{
		nen[i] = ft_strdup(en->env[i]);
		i++;
	}
	nen[i] = ft_strdup(val);
	nen[i + 1] = NULL;
	en->env = nen;
}

void		sh_btse_mod_env(char *expr, t_en *en)
{
	int		i;
	char	*name;

	i = 0;
	while (expr[i] != '=')
		i++;
	name = ft_strsub(expr, 0, i);
	if (expr[i + 1] == '"')
	{
		while (expr[i + 1] && expr[i + 1] != '"')
		{
			expr[i] = expr[i + 1];
			i++;
		}
		expr[i + 1] = '\0';
	}
	if ((i = sh_getenv(en, name)) == -1)
		sh_btse_add_env(expr, en);
	else
		en->env[i] = ft_strdup(expr);
}

static char	*sh_btse_create_entry(char *name, char *value)
{
	char	*nstr;

	nstr = ft_strdup(name);
	nstr = ft_strjoin(nstr, "=");
	nstr = ft_strjoin(nstr, value);
	return (nstr);
}

void		sh_builtin_setenv(t_en *en)
{
	int		i;

	i = 0;
	while (en->arg[++i])
	{
		if (ft_strstr(en->arg[i], "="))
			sh_btse_mod_env(en->arg[i], en);
		else
		{
			if (en->arg[i + 1])
			{
				if (sh_getenv(en, en->arg[i]) == -1)
					sh_btse_add_env(CREATE_ENTRY, en);
				i++;
			}
			else
			{
				sh_error_setenv(2);
				break ;
			}
		}
	}
}
