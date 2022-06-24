/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updateexit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:29:43 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/24 17:18:17 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setlastcommand(t_shell *shell)
{
	t_cmdgroup	*grp;
	t_token		*token;

	grp = shell->cmdgroup;
	token = grp->tokens;
	if (grp->next != NULL)
		shell->lastcmd = NULL;
	while (token != NULL)
	{
		if (token->type == ARG || token->type == COMMAND)
			shell->lastcmd = token->str;
		else
			shell->lastcmd = "";
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
