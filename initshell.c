/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 01:53:26 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/11 17:51:50 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	incrementshlvl(t_shell *shell)
{
	char	*shlvl;
	char	*shlvl_arg;
	int		shlvl_int;
	int		index;

	shlvl = ft_getenv(shell->sh_env, "SHLVL");
	if (shlvl[0] == '-' && ft_strisnum(shlvl, 1))
		shlvl_int = 0;
	else if (!ft_strisnum(shlvl, 1))
		shlvl_int = 1;
	else
		shlvl_int = ft_atoi(shlvl) + 1;
	shlvl = ft_itoa(shlvl_int);
	shlvl_arg = ft_strjoin("SHLVL=", shlvl);
	free(shlvl);
	index = isexisting(shell, shlvl_arg);
	replacevar(shell, shlvl_arg, index);
	free(shlvl_arg);
}

void	resetfd(t_shell *shell)
{
	shell->fdin = -1;
	shell->fdout = -1;
}

void	initshell(t_shell *shell, char **envp)
{
	shell->cmdline = NULL;
	shell->cmdgroup = NULL;
	shell->sh_env = NULL;
	shell->cmdgrpcount = 0;
	shell->exit = 0;
	shell->fdstdin = dup(STDIN);
	shell->fdstdout = dup(STDOUT);
	resetfd(shell);
	clone_env(envp, shell);
	incrementshlvl(shell);
}
