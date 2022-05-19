/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:25:25 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/19 18:25:26 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clearmemory(t_cmd *cmd)
{
	t_token	*temp;

	temp = cmd->tokens;
	while (cmd->tokens != NULL)
	{
		temp = cmd->tokens->next;
		free(cmd->tokens);
		cmd->tokens = temp;
	}
}