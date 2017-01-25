/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_en.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemarch <elemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 12:58:01 by elemarch          #+#    #+#             */
/*   Updated: 2015/06/01 12:58:05 by elemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#include "../ft_sh1.h"

char	**sh_en_findpath(char **env)
{
	char	*path;
	int		i;

	system("afplay sounds/start.wav &");
	i = 0;
	while (env && env[i])
	{
		if (ft_strstr(env[i], "PATH"))
			break ;
		i++;
	}
	if (env)
		path = ft_strccat(ft_strdup(&(env[i][5])), ":.:");
	else
		path = ft_strdup("./:");
	return (ft_strsplit(path, ':'));
}

void	sh_en_setup(t_en *en, char **env, int ac, char **av)
{
	int		i;
	char	buf[PATHSIZE];

	(void)ac;
	(void)av;
	i = 0;
	en->env = env;
	en->com = NULL;
	en->arg = NULL;
	en->usr = ft_strdup(sh_getenv_val(en, "USER"));
	if (!ft_strcmp(en->usr, "{NULL}"))
		en->usr = ft_strdup("anonymous");
	en->path = sh_en_findpath(env);
	while (en->path[i])
	{
		en->path[i] = ft_strccat(en->path[i], "/");
		i++;
	}
	chdir(sh_getenv_val(en, "PWD"));
	getcwd(buf, PATHSIZE);
	en->com = ft_strccat("setenv PWD=", buf);
	sh_execute(en);
	en->com = NULL;
	en->arg = NULL;
}
