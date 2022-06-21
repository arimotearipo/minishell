/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:07:38 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/21 23:17:37 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Moved to heredoc.c
// static void	open_heredoc(t_shell *shell, t_token *token)
// {
// 	char	*line;

// 	signal(SIGINT, SIG_DFL);
// 	close(shell->fdin);
// 	dup2(shell->fdstdin, STDIN);
// 	unlink(".ttiyut7");
// 	shell->fdin = open(".ttiyut7", O_WRONLY | O_TRUNC | O_CREAT | O_EXCL, 0600);
// 	if (shell->fdin == -1)
// 		exit(1);
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!ft_strcmp(line, token->next->str) || line == NULL)
// 		{
// 			free(line);
// 			line = NULL;
// 			break ;
// 		}
// 		translateinheredoc(shell, &line);
// 		ft_putendl_fd(line, shell->fdin);
// 		free(line);
// 		line = NULL;
// 	}
// 	close(shell->fdin);
// 	exit(0);
// }

void	open_heredoc(t_shell *shell, t_cmdgroup *grp, t_token *token)
{
	int		status;
	int		readbytes;
	pid_t	pid;
	int		fd;
	char	buf[PATH_MAX];

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		dup2(shell->fdstdin, STDIN_FILENO);
		unlink(".ttiyut7");
		shell->fdin = open(".ttiyut7", O_WRONLY | O_TRUNC | O_CREAT |
			O_EXCL, 0600);
		open_heredoc_child(shell, grp, token);
		ft_putstr_fd(grp->heredoc, shell->fdin);
		close(shell->fdin);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(-1, &status, 0);
		fd = open(".ttiyut7", O_RDONLY);
		readbytes = read(fd, buf, PATH_MAX);
		buf[readbytes] = '\0';
		grp->heredoc = ft_strdup(buf);
		close(fd);
		shell->eofexit = status;
	}
}

void	open_redirectioninput(t_shell *shell, t_token *token)
{
	close(shell->fdin);
	dup2(shell->fdstdin, STDIN);
	shell->fdin = open(token->next->str, O_RDONLY, 0700);
	if (shell->fdin == -1)
		return ;
	dup2(shell->fdin, STDIN);
}

void	open_redirectionright(t_shell *shell, t_token *tkn)
{
	char	*fd;

	fd = tkn->next->str;
	close(shell->fdout);
	dup2(shell->fdstdout, STDOUT);
	if (tkn->type == OUTPUT)
		shell->fdout = open(fd, O_CREAT | O_WRONLY | O_TRUNC, 0700);
	else if (tkn->type == APPEND)
		shell->fdout = open(fd, O_CREAT | O_WRONLY | O_APPEND, 0700);
	if (shell->fdout == -1)
		return ;
	dup2(shell->fdout, STDOUT);
}

void	open_redirectionread(t_shell *shell, t_cmdgroup *grp, t_token *tkn)
{
	(void)tkn;
	(void)grp;
	unlink(".ttiyut7");
	shell->fdin = open(".ttiyut7", O_CREAT | O_WRONLY | O_TRUNC, 0700);
	ft_putstr_fd(grp->heredoc, shell->fdin);
	close(shell->fdin);
	shell->fdin = open(".ttiyut7", O_RDONLY);
	dup2(shell->fdin, STDIN_FILENO);
	close(shell->fdin);
	// ft_putstr_fd(grp->heredoc, 1);
	// perror("assigned to ttiyut7\n");
	// shell->fdin = open(".ttiyut7", O_RDONLY);
	// dup2(shell->fdin, STDIN_FILENO);
	// close(shell->fdin);
	// ft_putstr_fd(grp->heredoc, STDIN_FILENO);
}

void	exe_redirection(t_shell *shell, t_cmdgroup *grp)
{
	t_token	*first;

	first = grp->tokens;
	// while (grp->tokens != NULL)
	// {
	// 	if (grp->tokens->type == RDINPUT)
	// 	{
	// 		shell->heredocflag = 1;
	// 		open_redirectionread(shell, grp->tokens);
	// 	}
	// 	grp->tokens = grp->tokens->next;
	// }
	// grp->tokens = first;
	while (grp->tokens != NULL)
	{
		if (grp->tokens->type >= INPUT && grp->tokens->type <= RDINPUT)
		{
			if (grp->tokens->type == OUTPUT || grp->tokens->type == APPEND)
			{
				open_redirectionright(shell, grp->tokens);
				shell->redirflag = 1;
			}
			else if (grp->tokens->type == INPUT)
				open_redirectioninput(shell, grp->tokens);
			else if (grp->tokens->type == RDINPUT)
			{
				// printf("TESTINGSASDASDASD\n");
				open_redirectionread(shell, grp, grp->tokens);
			}
		}
		grp->tokens = grp->tokens->next;
	}
	grp->tokens = first;
}
