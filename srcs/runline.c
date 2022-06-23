/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:19:31 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/23 19:14:02 by wwan-taj         ###   ########.fr       */
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
	shell->heredocflag = 0;
}

void	runprogramchild(t_shell *shell, t_cmdgroup *grp)
{
	pid_t	pid;
	int		status;

	if (shell->cmdgrpcount == 1)
	{
		run_program(shell, grp);
		dup2(shell->fdstdin, STDIN);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		run_program(shell, grp);
		exit(shell->exit);
	}
	else
	{
		waitpid(-1, &status, 0);
		shell->exit = status;
		dup2(shell->fdstdin, STDIN);
	}
}

void	runline(t_shell *shell, t_cmdgroup *grp)
{
	t_cmdgroup	*first;

	first = grp;
	while (grp != NULL)
	{	
		resetflags(shell);
		if (exe_redirection(shell, grp) == -1)
		{
			printerror(shell, "Error. No such file\n", SYNTAXERROR);
			closeandresetfd(shell, 0);
			grp = grp->next;
			continue ;
		}
		if (shell->eofexit == 2)
		{
			closeandresetfd(shell, 1);
			break ;
		}
		if (grp->next == NULL)
			runprogramchild(shell, grp);
		else
			piping(shell, grp);
		closeandresetfd(shell, 0);
		grp = grp->next;
	}
	while (wait(NULL) != -1)
		;
	grp = first;
}
