/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemarch <elemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 12:57:36 by elemarch          #+#    #+#             */
/*   Updated: 2015/08/18 16:30:32 by elemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH1_H
# define FT_SH1_H

# include <stdio.h>
# include <unistd.h>
# include "libft/libft.h"
# include <dirent.h>

# define PATHSIZE 2048
# define BUFF_SIZE 11

/*
** ================================ STRUCTURE =============================== **
**  char**	| env	| environment var copy									  **
**  char**	| path	| splitted PATH environment entry						  **
**  char**	| arg	| command arguments list								  **
**  char*	| com	| command without arguments (first, entered line)		  **
**  char*	| usr	| USER environment entry								  **
** ========================================================================== **
*/

typedef struct	s_en
{
	char		**env;
	char		**path;
	char		**arg;
	char		**com_tab;
	char		*com;
	char		*usr;
}				t_en;

/*
** ================================ SRC LIST ================================ **
**  sh_en_setup | setup the t_en *en var with the envirnonment variable		  **
**  sh_builtin	| test if the command is a builtin, if so execute it.		  **
**  sh_error	| error manager for sh (see below)							  **
**  sh_split	| split command and arguments								  **
**  sh_getenv	| search for str entry into the environment variable.		  **
**  			| returns th index of the entry or -1 if not found			  **
**  sh_getenv	| search for str entry into the environment variable.		  **
**  			| returns its value, or NULL if not found					  **
** ========================================================================== **
*/

void			sh_en_setup(t_en *en, char **env, int ac, char **av);
int				sh_builtin(t_en *en);
int				sh_split(t_en *en);
int				sh_getenv(t_en *en, const char *str);
char			*sh_getenv_val(t_en *en, const char *str);
void			sh_execute(t_en *en);

/*
** =============================== ERROR LIST =============================== **
** error	| 1	| command not found											  **
**			| 2	| no such file or directory									  **
** setenv	| 1	| need arguments											  **
**			| 2	| found name without value									  **
** ========================================================================== **
*/

int				sh_error(t_en *en, int err);
void			sh_error_setenv(int err);

/*
** ================================ BUILTINS ================================ **
*/

void			sh_builtin_setenv(t_en *en);
void			sh_btse_mod_env(char *expr, t_en *en);
void			sh_builtin_unsetenv(t_en *en);
void			sh_builtin_cd(t_en *en);

#endif
