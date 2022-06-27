/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:59:46 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/27 17:33:39 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
This will be called upon everytime the 'cd' built-in function is called.
It will update the value of 'PWD' and 'OLDPWD' respectively in the env
2D array. It will replace the current value if it already exists and
will append to the end if doesn't (in the case of being unset before the
calling of 'cd).
*/
static void	update_pwd_and_oldpwd(t_shell *shell, char *oldpwd)
{
	char	*newarg;
	char	*dir;
	char	*var;
	int		oldpwdindex;
	int		pwdindex;

	newarg = malloc(sizeof(char) * PATH_MAX);
	dir = getcwd(newarg, PATH_MAX);
	oldpwdindex = getvarindex(shell, "OLDPWD");
	pwdindex = getvarindex(shell, "PWD");
	var = ft_strjoin("OLDPWD=", oldpwd);
	if (oldpwdindex != -1)
		replacevar(shell, var, oldpwdindex);
	else
		insertvar(shell, var);
	free(var);
	var = ft_strjoin("PWD=", dir);
	if (pwdindex != -1)
		replacevar(shell, var, pwdindex);
	else
		insertvar(shell, var);
	free(var);
	free(oldpwd);
	free(newarg);
}

void	cd_to_oldpwd(t_shell *shell)
{
	char	*oldpwdpath;

	if (ft_getenv(shell->sh_env, "OLDPWD") == NULL)
	{
		printerror(shell, "OLDPWD not set\n", SYNTAXERROR);
		return ;
	}
	if (cd(shell, ft_getenv(shell->sh_env, "OLDPWD")) != -1)
	{
		oldpwdpath = ft_getenv(shell->sh_env, "PWD");
		ft_putendl_fd(oldpwdpath, 1);
	}
}

void	check_pwd_and_oldpwd(t_shell *shell)
{
	char	*pwd;
	char	*oldpwd;
	char	*home;

	if (getvarindex(shell, "PWD") == -1)
	{
		pwd = ft_strjoin("PWD=", getenv("PWD"));
		insertvar(shell, pwd);
		free(pwd);
	}
	else if (getvarindex(shell, "OLDPWD") == -1)
	{
		oldpwd = ft_strjoin("OLDPWD=", getenv("OLDPWD"));
		insertvar(shell, oldpwd);
		free(oldpwd);
	}
	else if (getvarindex(shell, "HOME") == -1)
	{
		home = ft_strjoin("HOME=", getenv("HOME"));
		insertvar(shell, home);
		free(home);
	}
}

int	cd(t_shell *shell, char *arg)
{
	char	*oldpwd;
	int		tilde;

	if (arg[0] == '-' && arg[1] == '\0')
	{
		cd_to_oldpwd(shell);
		return (0);
	}
	oldpwd = ft_strdup(ft_getenv(shell->sh_env, "PWD"));
	tilde = 0;
	if (arg[0] == '~')
	{
		arg = expandpath(arg);
		tilde = 1;
	}
	if (chdir(arg) == -1)
	{
		printerror(shell, "Error. No such file or directory.\n", 1);
		free(oldpwd);
		return (-1);
	}
	if (tilde == 1)
		free(arg);
	update_pwd_and_oldpwd(shell, oldpwd);
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
		if (ft_getenv(shell->sh_env, "HOME") == NULL)
		{
			printerror(shell, "HOME not set\n", 1);
			return ;
		}
		cd(shell, ft_getenv(shell->sh_env, "HOME"));
		return ;
	}
	check_pwd_and_oldpwd(shell);
	cd(shell, cmd->tokens->str);
	cmd->tokens = first;
}
