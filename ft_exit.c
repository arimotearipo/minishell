/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:19:43 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/06/12 18:28:46 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *shell, t_cmdgroup *cmd, t_token *tkn, int opt)
{
	int	exitstatus;

	if (opt == 1)
	{
		ft_putendl_fd("exit", 1);
		printerror(shell, "bash: exit: numeric argument required\n", 1);
		clearmemory(shell, cmd);
		exit(255);
	}
	else if (opt == 2)
	{
		exitstatus = ft_atoi(tkn->str);
		ft_putendl_fd("exit", 1);
		clearmemory(shell, cmd);
		exit(exitstatus % 256);
	}
	else if (opt == 3)
	{	
		ft_putendl_fd("exit", 1);
		clearmemory(shell, cmd);
		exit(0);
	}
}

int	exe_exit(t_shell *shell, t_cmdgroup *cmd)
{
	t_token	*tokens;

	tokens = cmd->tokens->next;
	if (tokens != NULL && tokens->next != NULL)
		printerror(shell, "bash: exit: too many arguments\n", 1);
	else if (tokens != NULL)
	{
		if (ft_strisnum(tokens->str, 1) == 0)
			ft_exit(shell, cmd, tokens, 1);
		else
			ft_exit(shell, cmd, tokens, 2);
	}
	else
		ft_exit(shell, cmd, tokens, 3);
	return (0);
}
