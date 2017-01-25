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

/*
** Fork() causes creation of a new process
**		fork() returns a value of 0 to the child process and returns the process
**		ID of the child process to the parent process.
** if pid == 0, that means we're in the child process.
** Execve() transforms the calling process into a new process
**	(path[], argv[][], envp[])
*/

int		sh_envtest(char **env)
{
	t_en	tenv;

	tenv.env = env;
	if (sh_getenv(&tenv, "PATH") == -1)
		return (0);
	if (sh_getenv(&tenv, "HOME") == -1)
		return (0);
	if (sh_getenv(&tenv, "PWD") == -1)
		return (0);
	if (sh_getenv(&tenv, "OLDPWD") == -1)
		return (0);
	return (1);
}

int		sh_isempty(char *str)
{
	str = ft_strtrim(str);
	if (!str[0])
		return (1);
	return (0);
}

void	sh_execute(t_en *en)
{
	pid_t	cpid;
	int		i;

	if (!sh_split(en))
		return ;
	if (sh_builtin(en) || sh_isempty(en->com))
		return ;
	cpid = fork();
	if (cpid == 0)
	{
		i = 0;
		if (en->com[0] == '\0' || !execve(en->com, en->arg, en->env))
			return ;
		while (en->path && en->path[i])
		{
			if (!execve(ft_strccat(en->path[i], en->com), en->arg, en->env))
				break ;
			i++;
		}
		if (en->path && !en->path[i])
			sh_error(en, 1);
		exit(0);
	}
	else
		waitpid(cpid, 0, 0);
}

int		sh_exec_loop(t_en *en)
{
	int		i;

	i = 0;
	while (en->com_tab[i])
	{
		en->com = ft_strdup(ft_strtrim(en->com_tab[i]));
		if (!ft_strcmp(en->com, "exit"))
		{
			system("afplay sounds/exit.wav &");
			return (0);
		}
		sh_execute(en);
		en->com = NULL;
		i++;
	}
	return (1);
}

int		main(int ac, char **av, char **env)
{
	char	buf[BUFF_SIZE];
	int		ret;
	t_en	en;

	if (!sh_envtest(env))
		return (sh_error(NULL, 3));
	sh_en_setup(&en, env, ac, av);
	while (1)
	{
		ft_putstrs("$\033[31m$S\033[0m in ", en.usr);
		ft_putstrs("\033[32m$S\033[0m:\n\t> ", sh_getenv_val(&en, "PWD"));
		while ((ret = read(0, buf, BUFF_SIZE - 1)) > 0)
		{
			buf[ret] = '\0';
			en.com = ft_strccat(en.com, buf);
			if (buf[ret - 1] == '\n')
				break ;
		}
		en.com = ft_strtrim(en.com);
		en.com_tab = ft_strsplit(en.com, ';');
		if (sh_exec_loop(&en) == 0)
			break ;
	}
	return (0);
}
