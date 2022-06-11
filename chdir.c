/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:59:46 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/11 14:52:18 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Might need to free home variable
char	*expandpath(char *arg)
{
	char	*home;
	char	*remainderpath;
	char	*fullpath;

	home = getenv("HOME");
	remainderpath = ft_substr(arg, 1, ft_strlen(arg));
	fullpath = ft_strjoin(home, remainderpath);
	free(remainderpath);
	return (fullpath);
}

static void	changevar(t_shell *shell, char *oldpwd)
{
	char	*newarg;
	char	*dir;
	int		m;

	newarg = malloc(sizeof(char) * PATH_MAX);
	dir = getcwd(newarg, PATH_MAX);
	m = getvarindex(shell, "PWD");
	free(shell->sh_env[m]);
	shell->sh_env[m] = ft_strjoin("PWD=", dir);
	free(shell->sh_env[m + 1]);
	shell->sh_env[m + 1] = ft_strjoin("OLDPWD=", oldpwd);
	free(oldpwd);
	free(newarg);
}

static int	cd(t_shell *shell, char *arg)
{
	char	*oldpwd;
	int		tilde;

	tilde = 0;
	oldpwd = ft_strdup(ft_getenv(shell->sh_env, "PWD"));
	if (arg[0] == '~')
	{
		arg = expandpath(arg);
		tilde = 1;
	}
	if (chdir(arg) == -1)
	{
		printerror(shell, "Error. No such file or directory.\n", 1);
		return (-1);
	}
	if (tilde == 1)
		free(arg);
	changevar(shell, oldpwd);
	return (0);
}

void	exe_cd(t_shell *shell, t_cmdgroup *cmd)
{
	t_token	*first;

	first = cmd->tokens;
	cmd->tokens = cmd->tokens->next;
	if (cmd->tokens == NULL)
	{
		cmd->tokens = first;
		cd(shell, getenv("HOME"));
		return ;
	}
	cd(shell, cmd->tokens->str);
	cmd->tokens = first;
}
