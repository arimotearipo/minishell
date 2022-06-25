/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:22:12 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/25 16:18:22 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	checkline(t_shell *shell)
{
	if (shell->exit == 0)
		emptycommand(shell);
	if (shell->exit == 0)
		redirectionerror(shell);
}

int	isnoterror(int errornum)
{
	if (errornum == SYNTAXERROR)
		return (0);
	if (errornum == NOCOMMAND)
		return (0);
	if (errornum == NOEXECUTE)
		return (0);
	if (errornum == UNEXPECTEDTOKEN)
		return (0);
	if (errornum == REDIRERROR)
		return (0);
	return (1);
}
