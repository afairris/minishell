/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemarch <elemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 12:57:55 by elemarch          #+#    #+#             */
/*   Updated: 2015/06/01 12:57:57 by elemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#include "../ft_sh1.h"

void	sh_builtin_env(t_en *en)
{
	int		i;
	int		j;

	i = 0;
	while (en->env[i])
	{
		j = 0;
		ft_putstr("\033[34m");
		while (en->env[i][j] != '=')
		{
			ft_putchar(en->env[i][j]);
			j++;
		}
		j += 1;
		ft_putstr("\033[30m = \033[0m");
		while (en->env[i][j])
		{
			ft_putchar(en->env[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

void	sh_builtin_env_printcust(t_en *en)
{
	int		i;
	int		c;

	c = 0;
	i = (ft_strcmp(en->arg[1], "-i") ? 1 : 2);
	while (en->arg[i])
	{
		ft_putstr("\033[34m");
		while (en->arg[i][c] && en->arg[i][c] != '=')
		{
			ft_putchar(en->arg[i][c]);
			c++;
		}
		ft_putstr("\033[30m = \033[0m");
		c++;
		while (en->arg[i][c])
		{
			ft_putchar(en->arg[i][c]);
			c++;
		}
		ft_putchar('\n');
		i++;
	}
}

void	sh_builtin_env_custom(t_en *en)
{
	int		i;

	i = 2;
	if (ft_strcmp(en->arg[1], "-i") && !ft_strchr(en->arg[1], '='))
	{
		sh_error(en, 2);
		return ;
	}
	while (en->arg[i])
	{
		if (!ft_strchr(en->arg[i], '='))
		{
			sh_error(en, 4);
			return ;
		}
		i++;
	}
	if (ft_strcmp(en->arg[1], "-i"))
		sh_builtin_env(en);
	sh_builtin_env_printcust(en);
}

int		sh_builtin(t_en *en)
{
	if (!(!ft_strcmp(en->com, "cd") || !ft_strcmp(en->com, "env") ||
		!ft_strcmp(en->com, "setenv") || !ft_strcmp(en->com, "unsetenv")
		|| !ft_strcmp(en->com, "uuddlrlrba")))
		return (0);
	else
	{
		if (!ft_strcmp(en->com, "cd"))
			sh_builtin_cd(en);
		else if (!ft_strcmp(en->com, "setenv"))
			sh_builtin_setenv(en);
		else if (!ft_strcmp(en->com, "uuddlrlrba"))
			system("afplay sounds/konami.wav &");
		else if (!ft_strcmp(en->com, "unsetenv"))
			sh_builtin_unsetenv(en);
		else if (!ft_strcmp(en->com, "env"))
		{
			if (en->arg[1])
				sh_builtin_env_custom(en);
			else
				sh_builtin_env(en);
		}
	}
	return (1);
}
