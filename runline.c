/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:19:31 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/13 22:00:53 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closefd(t_shell *shell)
{
	if (shell->fdin > 0)
	{
		close(shell->fdin);
		// dup2(shell->fdstdin, STDIN);
	}
	if (shell->fdout > 0)
	{
		close(shell->fdout);
		dup2(shell->fdstdout, STDOUT);
	}
	unlink(".ttiyut7");
}

void	piping(t_shell *shell, t_cmdgroup *grp)
{
	pid_t	pid;
	int		fd[2];

	(void)shell;
	(void)grp;
	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		close(fd[0]);
		// printf("BEFORE RUN\n");
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
		// printf("IN ELSE\n");
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(-1, NULL, 0);
		// printf("EXITED CHILD\n");
	}
	// if (grp->next == NULL)
	// 	dup2(shell->fdstdin, STDIN);
}

void	runline(t_shell *shell, t_cmdgroup *grp)
{
	t_cmdgroup	*first;

	first = grp;
	while (grp != NULL)
	{
		shell->redirflag = 0;
		exe_redirection(shell, grp);
		if (grp->next == NULL)
		{
			run_program(shell, grp);
			dup2(shell->fdstdin, STDIN);
		}
		else
		{
			// run_program(shell, grp);
			piping(shell, grp);
		}
		closefd(shell);
		resetfd(shell);
		grp = grp->next;
	}
	grp = first;
}
