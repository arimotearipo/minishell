/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:25:25 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/20 12:26:20 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	clearmemory(t_cmd *cmd)
// {
// 	t_token	*temp;

// 	temp = cmd->tokens;
// 	while (cmd->tokens != NULL)
// 	{
// 		temp = cmd->tokens->next;
// 		free(cmd->tokens->str);
// 		free(cmd->tokens);
// 		cmd->tokens = temp;
// 	}
// }

void	clearmemory(t_cmd *cmd)
{
	t_token *temp;
	t_token *lst;

	lst = cmd->tokens;
	while(lst)
	{
		temp = lst->next;
		free(lst->str);
		free(lst);
		lst = temp;
	}
	cmd->tokens = NULL;
}