/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:25:25 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/22 15:31:09 by wwan-taj         ###   ########.fr       */
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

void	clearmemory(t_shell *shell, t_cmdgroup *lst)
{
	t_cmdgroup	*temp;

	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
		ft_freelst(&(lst->tokens));
		if (lst->heredoc != NULL)
		{
			free(lst->heredoc);
			lst->heredoc = NULL;
		}
		temp = lst->next;
		free(lst);
		lst = temp;
	}
	free(shell->cmdline);
	shell->cmdline = NULL;
}

void	ft_free4str(char *a, char *b, char *c, char *d)
{
	if (a != NULL)
		free(a);
	if (b != NULL)
		free(b);
	if (c != NULL)
		free(c);
	if (d != NULL)
		free(d);
}
