/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 01:53:26 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/07 16:11:45 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initshell(t_shell *shell, char **envp)
{
	shell->cmdline = NULL;
	shell->cmdgroup = NULL;
	shell->sh_env = NULL;
	shell->cmdgrpcount = 0;
	shell->exit = 0;
	clone_env(envp, shell);
}
