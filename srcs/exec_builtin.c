/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 22:26:15 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/20 20:25:39 by mahmad-j         ###   ########.fr       */
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
	t_cmdgroup	*grp;

	grp = group;
	while (grp->tokens != NULL)
	{
		if (grp->tokens->type == COMMAND || grp->tokens->type == ARG)
		{
			exe_program(shell, grp->tokens, grp->tokens->str);
			break ;
		}
		grp->tokens = grp->tokens->next;
	}
}
