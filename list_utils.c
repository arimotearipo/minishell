/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:21:35 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/19 18:21:35 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	filllst(t_token **lst, char *str, int i, int len)
{
	t_token	*tokens;
	t_token	*last;

	if (len < 0)
		return ;
	last = *lst;
	tokens = malloc(sizeof(t_token));
	tokens->str = ft_substr(str, i, len);
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
