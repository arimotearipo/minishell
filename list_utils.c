/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:21:35 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/20 11:30:11 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
