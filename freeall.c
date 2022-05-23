/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:25:25 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/23 11:09:45 by mahmad-j         ###   ########.fr       */
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

void	ft_freelst(t_token **list)
{
	t_token	*l;
	t_token	*next;

	l = *list;
	while (l)
	{
		next = l->next;
		free(l->str);
		free(l);
		l = next;
	}
	*list = NULL;
}

// void	clearmemory(t_cmdgroup *lst)
// {
// 	ft_freelst(&(lst->tokens));
// 	ft_freelst(&(lst));
// }

// void	cleartokenmemory(t_token **lst)
// {
// 	while (*lst != NULL)
// 	{
// 		free((*lst)->str);
// 		(*lst)->str = NULL;
// 		(*lst) = (*lst)->next;
// 		if ((*lst) != NULL && (*lst)->prev != NULL)
// 		{
// 			free((*lst)->prev);
// 			(*lst)->prev = NULL;
// 		}
// 	}
// }

void	clearmemory(t_cmdgroup *lst)
{
	t_cmdgroup	*temp;

	while (lst != NULL)
	{
		ft_freelst(&(lst->tokens));
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