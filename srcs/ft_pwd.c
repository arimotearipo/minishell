/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:44:33 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/06/08 15:21:29 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_pwd(t_shell *shell, t_cmdgroup *cmd)
{
	(void)shell;
	cmd->topass = malloc(PATH_MAX);
	if (getcwd(cmd->topass, PATH_MAX) == NULL)
		return (-1);
	printf("%s\n", cmd->topass);
	return (0);
}
