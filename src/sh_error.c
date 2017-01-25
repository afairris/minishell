/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemarch <elemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 12:58:01 by elemarch          #+#    #+#             */
/*   Updated: 2015/06/01 12:58:05 by elemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#include "../ft_sh1.h"

void		sh_error_setenv(int err)
{
	if (err == 1)
		ft_putendl("setenv: need arguments");
	if (err == 2)
		ft_putendl("setenv: found variable name without value.");
	ft_putendl("    formats:");
	ft_putendl("    name value => creates variable (does not overwrite)");
	ft_putendl("    name=value => creates variable (overwrites)");
}

int			sh_error(t_en *en, int err)
{
	system("afplay sounds/error.wav &");
	if (err == 1)
		ft_putstrs("minishell: command not found: $S\n", en->com);
	if (err == 2)
	{
		ft_putstrs("$S: no such file or directory: ", en->com);
		ft_putendl(en->arg[1]);
	}
	if (err == 3)
		ft_putendl("WARNING: Bad environment given. Shell not launching.");
	if (err == 4)
	{
		ft_putstrs("$S: no such file or directory: ", en->com);
		ft_putendl(en->arg[2]);
	}
	if (err == 5)
		ft_putendl("Double quotes error.");
	return (0);
}
