/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:25:25 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/23 17:21:53 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	clearmemory(t_cmdgroup *lst)
{
	t_cmdgroup	*temp;

	while (lst != NULL)
	{
		ft_freelst(&(lst->tokens));
		temp = lst->next;
		// printf("temp: %p\n", temp);
		free(lst);
		lst = temp;
	}
}