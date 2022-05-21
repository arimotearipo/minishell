/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:21:35 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/21 21:53:33 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	filllst(t_cmd *cmd, char *str, int i, int len)
{
	t_token **lst;
	t_token	*tokens;
	t_token	*last;

	lst = &(cmd->tokens);
	if (len < 0)
		printerror(cmd);
	last = *lst;
	tokens = malloc(sizeof(t_token));
	tokens->str = ft_substr(str, i, len);
	if (!tokens || !tokens->str)
		printerror(cmd);
	if (last == NULL)
	{
		*lst = tokens;
		(*lst)->next = NULL;
		return ;
	}		
	else
	{
		while (last->next)
			last = last->next; // Move current pointer to next list
		last->next = tokens;
		last->next->next = NULL;
	}
}
*/

t_token	*createlist(char *str, int i, int len)
{
	t_token	*newlist;

	if (!str || i < 0 || len < 0)
		return (NULL);
	newlist = malloc(sizeof(t_token));
	newlist->str = ft_substr(str, i, len);
	newlist->next = NULL;
	newlist->prev = NULL;
	newlist->type = COMMAND;
	return (newlist);
}

int	addlist(t_cmd *cmd, char *str, int i, int len)
{
	t_token	*lst;
	t_token	*temp;		// for future purpose in case of adding a *prev pointer to each node
	t_token	*newlist;

	newlist = createlist(str, i, len);
	if (!newlist)
		return (EXIT_FAILURE);
	lst = cmd->tokens;
	if (lst == NULL)
	{
		cmd->tokens = newlist;
		return (EXIT_SUCCESS);
	}
	while (lst->next != NULL)
	{
		temp = lst;		// for future purpose in case of adding a *prev pointer to each node
		lst = lst->next;
		lst->prev = temp; //for future purpose in case of adding a *prev pointer to each node
	}
	newlist->prev = lst;	// for future purpose in case of adding a *prev pointer to each node
	lst->next = newlist;
	return (EXIT_SUCCESS);
}

void	showlist(t_cmd *cmd)
{
	t_token *lst;

	lst = cmd->tokens;
	while (lst != NULL)
	{
		printf("prev addr: %p my addr: %p next addr: %p str: %s\n", lst->prev, lst, lst->next, lst->str);
		lst = lst->next;
	}
}