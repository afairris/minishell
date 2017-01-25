/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_bt_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemarch <elemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 12:57:55 by elemarch          #+#    #+#             */
/*   Updated: 2015/06/01 12:57:57 by elemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_sh1.h"

void			sh_bt_cd(t_en *en)
{
	char		*path;

	path = ft_strdup(sh_getenv_val(en, "HOME"));
	if (opendir(path))
	{
		en->com = ft_strccat("setenv OLDPWD=", sh_getenv_val(en, "PWD"));
		sh_execute(en);
		en->com = ft_strccat("setenv PWD=", sh_getenv_val(en, "HOME"));
		sh_execute(en);
	}
	else
		sh_error(en, 2);
}

void			sh_bt_cdm(t_en *en)
{
	char	*buf;

	en->arg[1] = ft_strdup(sh_getenv_val(en, "OLDPWD"));
	if (opendir(en->arg[1]))
	{
		buf = sh_getenv_val(en, "OLDPWD");
		en->com = ft_strccat("setenv OLDPWD=", sh_getenv_val(en, "PWD"));
		sh_execute(en);
		en->com = ft_strccat("setenv PWD=", buf);
		sh_execute(en);
	}
	else
		sh_error(en, 2);
}

void			sh_bt_cdret(t_en *en)
{
	int		i;

	en->arg[1] = ft_strdup(sh_getenv_val(en, "PWD"));
	if (opendir(en->arg[1]))
	{
		en->com = ft_strccat("setenv OLDPWD=", sh_getenv_val(en, "PWD"));
		sh_execute(en);
		en->com = ft_strccat("setenv PWD=", sh_getenv_val(en, "PWD"));
		i = ft_strlen(en->com);
		while (en->com[i] != '/')
			i--;
		en->com[i] = '\0';
		sh_execute(en);
	}
	else
		sh_error(en, 2);
}

char			*sh_rep_tilde(t_en *en, char *str)
{
	if (str[0] == '~')
		return (ft_strjoin(sh_getenv_val(en, "HOME"), &str[1]));
	else
		return (str);
}

void			sh_builtin_cd(t_en *en)
{
	char	*path;
	char	buf[PATHSIZE];

	if (!en->arg[1] || !ft_strcmp(en->arg[1], "~"))
		sh_bt_cd(en);
	else if (!ft_strcmp(en->arg[1], "-"))
		sh_bt_cdm(en);
	else if (!ft_strcmp(en->arg[1], ".."))
		sh_bt_cdret(en);
	else
	{
		if ((path = sh_rep_tilde(en, en->arg[1])) && opendir(path))
		{
			en->com = ft_strccat("setenv OLDPWD=", sh_getenv_val(en, "PWD"));
			sh_execute(en);
			en->com = ft_strccat("setenv PWD=", path);
			sh_execute(en);
		}
		else
			sh_error(en, 2);
	}
	chdir(sh_getenv_val(en, "PWD"));
	getcwd(buf, PATHSIZE);
	en->com = ft_strccat("setenv PWD=", buf);
	sh_execute(en);
}
