/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:21:32 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/20 12:24:40 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printerror(t_cmd *cmd)
{
	printf("ERROR\n");
	clearmemory(cmd);
	// system("leaks minishell");
	exit(EXIT_FAILURE);
}
