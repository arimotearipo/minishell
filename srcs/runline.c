/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:19:31 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/25 16:23:44 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	piping(t_shell *shell, t_cmdgroup *grp)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == -1)
		return ;
	cheese_sleep(5000000);
	if (pid == 0)
	{
		close(fd[0]);
		if (shell->redirflag == 1)
			run_program(shell, grp);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (shell->redirflag == 0)
			run_program(shell, grp);
		exit(shell->exit);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

void	runprogramchild(t_shell *shell, t_cmdgroup *grp)
{
	pid_t	pid;

	if (shell->cmdgrpcount == 1)
	{
		run_program(shell, grp);
		dup2(shell->fdstdin, STDIN);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		cheese_sleep(5000000);
		run_program(shell, grp);
		exit(shell->exit);
	}
	else
		dup2(shell->fdstdin, STDIN);
}

void	redirection_error(t_shell *shell, t_cmdgroup **grp)
{
	printerror(shell, "Error. No such file\n", SYNTAXERROR);
	closeandresetfd(shell, 0);
	*grp = (*grp)->next;
}

void	runline(t_shell *shell, t_cmdgroup *grp)
{
	t_cmdgroup	*grplist;

	grplist = grp;
	while (grplist != NULL)
	{	
		resetflags(shell);
		if (exe_redirection(shell, grplist) == -1)
		{
			redirection_error(shell, &(grplist));
			continue ;
		}
		if (shell->eofexit == 2)
		{
			closeandresetfd(shell, 1);
			break ;
		}
		if (grplist->next == NULL)
			runprogramchild(shell, grplist);
		else
			piping(shell, grplist);
		closeandresetfd(shell, 0);
		grplist = grplist->next;
	}
	while (wait(&(shell->exit)) != -1)
		;
	if (shell->cmdgrpcount > 1)
		shell->exit = WEXITSTATUS(shell->exit);
}
