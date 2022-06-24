/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 21:23:26 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/24 21:24:38 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// dup2(shell->fdstdin, STDIN); was removed after close(shell->fdin)
void	closeandresetfd(t_shell *shell, int opt)
{
	if (shell->fdin > 0)
	{
		close(shell->fdin);
		if (opt == 1)
			dup2(shell->fdstdin, STDIN);
	}
	if (shell->fdout > 0)
	{
		close(shell->fdout);
		dup2(shell->fdstdout, STDOUT);
	}
	unlink(".ttiyut7");
	resetfd(shell);
}

void	resetflags(t_shell *shell)
{
	shell->redirflag = 0;
	shell->eofexit = 0;
	shell->heredocflag = 0;
}
