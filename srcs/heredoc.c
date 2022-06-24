/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:56:57 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/24 15:19:27 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
To review the freeing of grp->heredoc
*/
void	open_heredoc_child(t_shell *shell, t_cmdgroup *grp, t_token *token)
{
	char	*line;

	(void)shell;
	(void)grp;
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, token->next->str) || line == NULL)
		{
			free(line);
			line = NULL;
			break ;
		}
		translateinheredoc(shell, &line);
		strjoinandfree(&(grp->heredoc), line);
		strjoinandfree(&(grp->heredoc), "\n");
		free(line);
		line = NULL;
	}
}

void	open_heredoc_parent(t_cmdgroup *grp)
{
	int		fd;
	int		readbytes;
	char	buf[PATH_MAX];

	fd = open(".ttiyut7", O_RDONLY);
	readbytes = read(fd, buf, PATH_MAX);
	buf[readbytes] = '\0';
	strjoinandfree(&(grp->heredoc), buf);
	close(fd);
}

void	open_heredoc(t_shell *shell, t_cmdgroup *grp, t_token *token)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		dup2(shell->fdstdin, STDIN_FILENO);
		unlink(".ttiyut7");
		shell->fdin = open(".ttiyut7", O_WRONLY | O_TRUNC | O_CREAT
				| O_EXCL, 0600);
		open_heredoc_child(shell, grp, token);
		ft_putstr_fd(grp->heredoc, shell->fdin);
		close(shell->fdin);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(-1, &status, 0);
		open_heredoc_parent(grp);
		shell->eofexit = status;
	}
}

/*
This function will go through the whole command line and find
the heredocs that needs to be opened. If found, it will prompt
the user for inputs and store the strings in a malloc char array
within the cmdgroup struct.
*/
void	runallheredocs(t_shell *shell, t_cmdgroup *grp)
{
	t_cmdgroup	*first;
	t_token		*firsttoken;

	first = grp;
	while (grp != NULL)
	{
		firsttoken = grp->tokens;
		while (grp->tokens != NULL)
		{
			if (grp->tokens->type == RDINPUT)
			{
				shell->heredocflag = 1;
				open_heredoc(shell, grp, grp->tokens);
			}
			grp->tokens = grp->tokens->next;
		}
		grp->tokens = firsttoken;
		grp = grp->next;
	}
	grp = first;
}
