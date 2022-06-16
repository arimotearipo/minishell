/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:59:46 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/16 20:00:55 by wwan-taj         ###   ########.fr       */
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
	int		m;
	int		n;

	newarg = malloc(sizeof(char) * PATH_MAX);
	dir = getcwd(newarg, PATH_MAX);
	n = getvarindex(shell, "OLDPWD");
	m = getvarindex(shell, "PWD");
	var = ft_strjoin("OLDPWD=", oldpwd);
	if (n != -1)
		replacevar(shell, var, n);
	else
		insertvar(shell, var);
	free(var);
	var = ft_strjoin("PWD", dir);
	if (m != -1)
		replacevar(shell, var, m);
	else
		insertvar(shell, var);
	free(var);
	free(oldpwd);
	free(newarg);
}

// To be reviewed later
// static void	cd_macro(t_shell *shell)
// {
// 	char	*newdir;
// 	char	*curdir;
// 	char	*oldpwdvar;
// 	char	*buf;
// 	int		m;

// 	buf = malloc(sizeof(char) * PATH_MAX);
// 	curdir = getcwd(buf, PATH_MAX);
// 	newdir = ft_getenv(shell->sh_env, "OLDPWD");
// 	if (newdir == NULL)
// 	{
// 		printerror(shell, "Error: OLDPWD not set\n", SYNTAXERROR);
// 		return ;
// 	}
// 	if (chdir(newdir) == -1)
// 	{
// 		printerror(shell, "Error. No such file or directory.\n", 1);
// 		return ;
// 	}
// 	oldpwdvar = ft_strjoin("OLDPWD=", curdir);
// 	m = isexisting(shell, oldpwdvar);
// 	if (m > -1)
// 		replacevar(shell, oldpwdvar, m);
// 	else
// 		insertvar(shell, oldpwdvar);
// 	free(oldpwdvar);
// }

static int	cd(t_shell *shell, char *arg)
{
	char	*oldpwd;
	int		tilde;

	tilde = 0;
	oldpwd = ft_strdup(getenv("PWD"));
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
		cd(shell, getenv("HOME"));
		return ;
	}
	cd(shell, cmd->tokens->str);
	cmd->tokens = first;
}
