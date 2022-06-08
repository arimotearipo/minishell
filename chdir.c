/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:59:46 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/08 14:50:47 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(t_shell *shell, char *arg)
{
	char	*oldpwd;
	char	*newarg;
	char	*dir;
	int		m;

	oldpwd = ft_strdup(ft_getenv(shell->sh_env, "PWD"));
	if (chdir(arg) == -1)
	{
		ft_putstr_fd("Error. Not a directory.\n", 2);
		return (-1);
	}
	newarg = malloc(sizeof(char) * PATH_MAX);
	dir = getcwd(newarg, PATH_MAX);
	m = getvarindex(shell, "PWD");
	free(shell->sh_env[m]);
	shell->sh_env[m] = ft_strjoin("PWD=", dir);
	free(shell->sh_env[m + 1]);
	shell->sh_env[m + 1] = ft_strjoin("OLDPWD=", oldpwd);
	free(oldpwd);
	free(newarg);
	return (0);
}

void	exe_cd(t_shell *shell, t_cmdgroup *grp)
{
	t_token	*first;

	first = grp->tokens;
	grp->tokens = grp->tokens->next;
	if (grp->tokens == NULL)
	{
		cd(shell, getenv("HOME"));
		return ;
	}
	cd(shell, grp->tokens->str);
	grp->tokens = first;
}
