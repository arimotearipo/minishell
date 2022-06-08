/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updateexit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:29:43 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/08 15:35:12 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	updateexitvalue(t_shell *shell)
{
	char	*exitvaluestr;
	char	*exitnum;

	exitnum = ft_itoa(shell->exit);
	exitvaluestr = ft_strjoin("?=", exitnum);
	unset(shell, "?");
	export(shell, exitvaluestr);
	free(exitnum);
	free(exitvaluestr);
}