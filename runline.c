/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:19:31 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/11 21:31:18 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closefd(t_shell *shell)
{
	if (shell->fdin > 0)
	{
		close(shell->fdin);
		dup2(shell->fdstdin, STDIN);
	}
	if (shell->fdout > 0)
	{
		close(shell->fdout);
		dup2(shell->fdstdout, STDOUT);
	}
	unlink(".ttiyut7");
}

void	runline(t_shell *shell, t_cmdgroup *grp)
{
	t_cmdgroup	*first;

	first = grp;
	while (grp != NULL)
	{
		exe_redirection(shell, grp);
		exe_builtin(shell);
		closefd(shell);
		resetfd(shell);
		grp = grp->next;
	}
	grp = first;
}
