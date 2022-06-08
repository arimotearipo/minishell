/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:44:33 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/06/08 14:54:03 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell, t_cmdgroup *cmd)
{
	(void)shell;
	cmd->topass = malloc(PATH_MAX);
	if (getcwd(cmd->topass, PATH_MAX) == NULL)
		return (-1);
	printf("%s", cmd->topass);
	return (0);
}
