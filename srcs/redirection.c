/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:07:38 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/24 15:57:13 by wwan-taj         ###   ########.fr       */
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
	t_token	*token;
	int		res;

	res = 0;
	token = grp->tokens;
	while (token != NULL)
	{
		if (token->type >= INPUT && token->type <= RDINPUT)
		{
			if (token->type == OUTPUT || token->type == APPEND)
			{
				open_redirectionright(shell, token);
				shell->redirflag = 1;
			}
			else if (token->type == INPUT)
				res = open_redirectioninput(shell, token);
			else if (token->type == RDINPUT)
				open_redirectionread(shell, grp, token);
			if (res == -1)
				return (res);
		}
		token = token->next;
	}
	return (0);
}
