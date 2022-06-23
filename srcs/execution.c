/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 22:26:15 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/23 23:12:06 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_program(t_shell *shell, t_token *token, char *str)
{
	str = ft_strtolower(str);
	if (ft_strcmp(str, "echo") == 0)
		exe_echo(shell, shell->cmdgroup, token);
	else if (ft_strcmp(str, "cd") == 0)
		exe_cd(shell, shell->cmdgroup);
	else if (ft_strcmp(str, "pwd") == 0)
		exe_pwd(shell, shell->cmdgroup);
	else if (ft_strcmp(str, "export") == 0)
		exe_export(shell, shell->cmdgroup, token);
	else if (ft_strcmp(str, "unset") == 0)
		exe_unset(shell, shell->cmdgroup, token);
	else if (ft_strcmp(str, "env") == 0)
		showenv(shell, token, 1);
	else if (ft_strcmp(str, "exit") == 0)
		exe_exit(shell, shell->cmdgroup);
	else
		ft_execve(shell, token, str);
}

void	run_program(t_shell *shell, t_cmdgroup *group)
{
	t_token	*first;

	first = group->tokens;
	while (group->tokens != NULL)
	{
		if (group->tokens->type == COMMAND || group->tokens->type == ARG)
		{
			exe_program(shell, group->tokens, group->tokens->str);
			break ;
		}
		group->tokens = group->tokens->next;
	}
	group->tokens = first;
}

void	execution(t_shell *shell, t_cmdgroup *grp)
{
	runallheredocs(shell, grp);
	runline(shell, grp);
}
