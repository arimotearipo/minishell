/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:21:32 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/30 16:11:50 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printerror(t_shell *shell, t_cmdgroup *cmd)
{
	printf("ERROR\n");
	clearmemory(shell, cmd);
	// system("leaks minishell");
	exit(EXIT_FAILURE);
}
