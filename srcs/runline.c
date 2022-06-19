/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:19:31 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/20 01:45:42 by wwan-taj         ###   ########.fr       */
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

void	piping(t_shell *shell, t_cmdgroup *grp)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		close(fd[0]);
		if (shell->redirflag == 1)
			run_program(shell, grp);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (shell->redirflag == 0)
			run_program(shell, grp);
		exit(0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

static void	resetflags(t_shell *shell)
{
	shell->redirflag = 0;
	shell->eofexit = 0;
}

void	runline(t_shell *shell, t_cmdgroup *grp)
{
	t_cmdgroup	*first;

	first = grp;
	while (grp != NULL)
	{	
		resetflags(shell);
		exe_redirection(shell, grp);
		if (shell->eofexit == 2)
		{
			closeandresetfd(shell, 1);
			break ;
		}
		if (grp->next == NULL)
		{
			run_program(shell, grp);
			dup2(shell->fdstdin, STDIN);
		}
		else
			piping(shell, grp);
		closeandresetfd(shell, 0);
		grp = grp->next;
	}
	setlastcommand(shell);
	while (wait(NULL) != -1)
		;
	grp = first;
}
