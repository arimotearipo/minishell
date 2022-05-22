/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:25:25 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/22 21:16:16 by wwan-taj         ###   ########.fr       */
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

void	cleartokenmemory(t_token *lst)
{
	while (lst != NULL)
	{
		free(lst->str);
		lst->str = NULL;
		lst = lst->next;
		if (lst != NULL && lst->prev != NULL)
		{
			free(lst->prev);
			lst->prev = NULL;
		}
	}
}

void	clearmemory(t_cmdgroup *lst)
{
	t_cmdgroup	*temp;

	while (lst != NULL)
	{
		cleartokenmemory(lst->tokens);
		temp = lst->next;
		free(lst);
		lst = NULL;
		lst = temp;
	}
}

// void	clearmemory(t_cmdgroup *cmd)
// {
// 	t_cmdgroup	*cmdtemp;
// 	t_cmdgroup 	*cmdlst;
// 	t_token		*tokenlst;

// 	cmdlst = cmd;
// 	while(cmdlst != NULL)
// 	{
// 		while (cmdlst->tokens != NULL)
// 		{
// 			tokenlst = cmdlst->tokens;
// 			free(cmdlst->tokens->str);
// 			cmdlst->tokens = cmdlst->tokens->next;
// 			free(tokenlst);
// 		}
// 		cmdtemp = cmdlst;
// 		cmdlst = cmdlst->next;
// 		free(cmdtemp);
// 	}
// 	cmd->tokens = NULL;
// }