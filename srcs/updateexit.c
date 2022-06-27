/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updateexit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:29:43 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/27 18:22:00 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setlastcommand(t_shell *shell)
{
	t_cmdgroup	*grp;
	t_token		*token;

	shell->lastcmd = ft_strdup("");
	if (shell->cmdgrpcount > 1)
		return ;
	grp = shell->cmdgroup;
	token = grp->tokens;
	while (token != NULL)
	{
		if (token->type == ARG || token->type == COMMAND)
		{
			free(shell->lastcmd);
			if (!ft_strcmp(shell->cmdgroup->tokens->str, "export"))
				shell->lastcmd = getvarname(token->str);
			else
				shell->lastcmd = ft_strdup(token->str);
		}
		token = token->next;
	}
}

void	updatelastcommand(t_shell *shell)
{
	char	*lastcmd;

	if (shell->cmdgroup == NULL || shell->cmdgroup->next != NULL)
		return ;
	lastcmd = ft_strjoin("_=", shell->lastcmd);
	unset(shell, "_");
	insertvar(shell, lastcmd);
	free(lastcmd);
}

/*
This function will only be called when the the exit value is
already present in the sh_env. It will update the value of '?'
to its latest value.
*/
void	updateexitvalue(t_shell *shell)
{
	char	*exitvaluestr;
	char	*exitnum;

	if (g_sigint == 1)
		exitnum = ft_itoa(g_sigint);
	else
		exitnum = ft_itoa(shell->exit);
	exitvaluestr = ft_strjoin("?=", exitnum);
	unset(shell, "?");
	insertvar(shell, exitvaluestr);
	free(exitnum);
	free(exitvaluestr);
	updatelastcommand(shell);
}
