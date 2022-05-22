/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:21:35 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/22 21:07:02 by wwan-taj         ###   ########.fr       */
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
	// newlist->type = identifytype(str);
	return (newlist);
}

t_cmdgroup	*creategroup(int count)
{
	t_cmdgroup	*newgroup;
	t_cmdgroup	*tmp;
	t_cmdgroup	*first;

	newgroup = malloc(sizeof(t_cmdgroup));
	newgroup->tokens = NULL;
	first = newgroup;
	tmp = newgroup;
	while(count--)
	{
		newgroup = malloc(sizeof(t_cmdgroup));
		newgroup->tokens = NULL;
		tmp->next = newgroup;
		tmp = tmp->next;
	}
	newgroup->next = NULL;
	return (first);
}

int	addlist(t_cmdgroup *cmd, char *str, int i, int len)
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

void	showlist(t_cmdgroup *cmd)
{
	t_token		*firsttoken;
	t_cmdgroup	*firstcmd;
	int			i;

	firstcmd = cmd;
	i = 0;
	while (cmd != NULL)
	{
		printf("%d\n", i);
		firsttoken = cmd->tokens;
		while (cmd->tokens != NULL)
		{
			printf("%s\n", cmd->tokens->str);
			cmd->tokens = cmd->tokens->next;
		}
		cmd->tokens = firsttoken;
		cmd = cmd->next;
		i++;
	}
	cmd = firstcmd;
}