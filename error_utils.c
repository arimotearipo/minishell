/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:22:12 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/02 18:29:30 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	checkline(t_shell *shell)
{
	if (shell->exit == 0)
		emptycommand(shell);
	if (shell->exit == 0)
		redirectionerror(shell);
	if (shell->exit == 0)
		checkfirsttoken(shell);
}

int	isnoterror(int errornum)
{
	if (errornum == SYNTAXERROR)
		return (0);
	if (errornum == NOCOMMAND)
		return (0);
	if (errornum == NOEXECUTE)
		return (0);
	return (1);
}
