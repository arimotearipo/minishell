/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:21:32 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/26 20:56:32 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirectioncheck(t_shell *shell, t_token *tokens)
{
	if (tokens->type >= INPUT && tokens->type <= RDINPUT)
	{
		if (tokens->next == NULL)
		{
			printerror(shell, "Error: Unexpected token\n", UNEXPTOKEN);
			return (0);
		}
		else if ((tokens->next->type >= INPUT && tokens->next->type <= RDINPUT))
		{
			printerror(shell, "Error: Unexpected token\n", UNEXPTOKEN);
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
			printerror(shell, "Error: Unexpected token\n", UNEXPTOKEN);
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
