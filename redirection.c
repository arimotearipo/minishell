/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:07:38 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/12 16:39:29 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_redirectionread(t_shell *shell, t_cmdgroup *grp, t_token *token)
{
	char	*line;

	(void)grp;
	close(shell->fdin);
	dup2(shell->fdstdin, STDIN);
	unlink(".ttiyut7");
	shell->fdin = open(".ttiyut7", O_WRONLY | O_TRUNC | O_CREAT | O_EXCL, 0600);
	if (shell->fdin == -1)
		return ;
	while (1)
	{
		write(0, "> ", 2);
		line = get_next_line(0);
		if (!ft_strcchr(line, token->next->str, '\n'))
		{
			free(line);
			line = NULL;
			break ;
		}
		ft_putstr_fd(line, shell->fdin);
		free(line);
		line = NULL;
	}
	close(shell->fdin);
	shell->fdin = open(".ttiyut7", O_RDONLY);
	dup2(shell->fdin, STDIN);
}

void	open_redirectioninput(t_shell *shell, t_cmdgroup *grp, t_token *token)
{
	(void)grp;
	close(shell->fdin);
	dup2(shell->fdstdin, STDIN);
	shell->fdin = open(token->next->str, O_RDONLY, 0700);
	if (shell->fdin == -1)
		return ;
	dup2(shell->fdin, STDIN);
}

void	open_redirectionright(t_shell *shell, t_cmdgroup *grp, t_token *tkn)
{
	char	*fd;

	fd = tkn->next->str;
	(void)grp;
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

void	exe_redirection(t_shell *shell, t_cmdgroup *grp)
{
	t_token	*first;

	first = grp->tokens;
	while (grp->tokens != NULL)
	{
		if (grp->tokens->type >= INPUT && grp->tokens->type <= RDINPUT)
		{
			if (grp->tokens->type == OUTPUT || grp->tokens->type == APPEND)
				open_redirectionright(shell, grp, grp->tokens);
			else if (grp->tokens->type == INPUT)
				open_redirectioninput(shell, grp, grp->tokens);
			else if (grp->tokens->type == RDINPUT)
				open_redirectionread(shell, grp, grp->tokens);
		}
		grp->tokens = grp->tokens->next;
	}
	grp->tokens = first;
}
