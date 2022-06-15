/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 22:26:15 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/15 22:27:19 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_program(t_shell *shell, t_token *token, char *str)
{
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
		showenv(shell);
	else if (ft_strcmp(str, "exit") == 0)
		exe_exit(shell, shell->cmdgroup);
	else
		ft_execve(shell, token, str);
}
