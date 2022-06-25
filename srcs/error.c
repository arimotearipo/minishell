/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:21:32 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/25 16:10:13 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This checkfirstoken() function might be redundant as checking for command
** not found is done on ft_execve()
*/
void	checkfirsttoken(t_shell *shell)
{
	t_cmdgroup	*cmd;
	t_cmdgroup	*first;

	cmd = shell->cmdgroup;
	first = cmd;
	while (cmd != NULL)
	{
		if (cmd->tokens->type < COMMAND || cmd->tokens->type > RDINPUT)
		{
			printerror(shell, "Error: Command not found\n", NOCOMMAND);
			return ;
		}
		cmd = cmd->next;
	}
	cmd = first;
}

int	redirectioncheck(t_shell *shell, t_token *tokens)
{
	if (tokens->type >= INPUT && tokens->type <= RDINPUT)
	{
		if (tokens->next == NULL)
		{
			printerror(shell, "Error: Unexpected token\n", REDIRERROR);
			return (0);
		}
		else if ((tokens->next->type >= INPUT && tokens->next->type <= RDINPUT))
		{
			printerror(shell, "Error: Unexpected token\n", SYNTAXERROR);
			return (0);
		}
	}
	return (1);
}

void	redirectionerror(t_shell *shell)
{
	t_cmdgroup	*cmd;
	t_token		*firsttoken;

	cmd = shell->cmdgroup;
	while (cmd != NULL)
	{
		firsttoken = cmd->tokens;
		while (cmd->tokens != NULL)
		{
			if (redirectioncheck(shell, cmd->tokens) == 0)
				return ;
			cmd->tokens = cmd->tokens->next;
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
			printerror(shell, "Error: Unexpected token\n", UNEXPECTEDTOKEN);
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
