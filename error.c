/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:21:32 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/01 21:36:56 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	checkline(t_shell *shell)
{
	emptycommand(shell);
	redirectionislast(shell);
}

void	redirectionislast(t_shell *shell)
{
	t_cmdgroup	*cmd;
	t_token		*firsttoken;
	
	cmd = shell->cmdgroup;
	while (cmd != NULL)
	{
		firsttoken = cmd->tokens;
		while (cmd->tokens->next != NULL)
			cmd->tokens = cmd->tokens->next;
		if (cmd->tokens->type >= INPUT && cmd->tokens->type <= RDINPUT)
		{
			printerror(shell, "Error: Unexpected token\n", SYNTAXERROR);
			return ;
		}
		cmd->tokens = firsttoken;
		cmd = cmd->next;
	}
}

void	emptycommand(t_shell *shell)
{
	t_cmdgroup	*cmd;
	t_token		*firsttoken;
	
	cmd = shell->cmdgroup;
	while (cmd != NULL)
	{
		firsttoken = cmd->tokens;
		if (cmd->tokens == NULL)
		{
			printerror(shell, "Error: Unexpected token\n", SYNTAXERROR);
			return ;
		}
		cmd->tokens = firsttoken;
		cmd = cmd->next;
	}
}

void	printerror(t_shell *shell, char *msg, int errortype)
{
	ft_putstr_fd(msg, 2);
	shell->exit = errortype;
}
