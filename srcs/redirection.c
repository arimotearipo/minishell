/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:07:38 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/24 02:39:33 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redirectioninput(t_shell *shell, t_token *token)
{
	close(shell->fdin);
	dup2(shell->fdstdin, STDIN);
	shell->fdin = open(token->next->str, O_RDONLY, 0700);
	if (shell->fdin == -1)
		return (-1);
	dup2(shell->fdin, STDIN);
	return (1);
}

void open_redirectionright(t_shell *shell, t_token *tkn)
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
	return ;
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
}

int	exe_redirection(t_shell *shell, t_cmdgroup *grp)
{
	t_token	*first;
	int		res;

	res = 0;
	first = grp->tokens;
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
				res = open_redirectioninput(shell, grp->tokens);
			else if (grp->tokens->type == RDINPUT)
				open_redirectionread(shell, grp, grp->tokens);
			if (res == -1)
				return (res);
		}
		grp->tokens = grp->tokens->next;
	}
	grp->tokens = first;
	return (0);
}
