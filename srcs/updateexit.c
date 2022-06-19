/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updateexit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:29:43 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/19 18:31:20 by mahmad-j         ###   ########.fr       */
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

void	updateexitvalue(t_shell *shell)
{
	char	*exitvaluestr;
	char	*exitnum;

	exitnum = ft_itoa(shell->exit);
	exitvaluestr = ft_strjoin("?=", exitnum);
	unset(shell, "?");
	insertvar(shell, exitvaluestr);
	free(exitnum);
	free(exitvaluestr);
	updatelastcommand(shell);
}
