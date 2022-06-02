/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:25:25 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/02 17:56:02 by wwan-taj         ###   ########.fr       */
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

	while (lst != NULL)
	{
		ft_freelst(&(lst->tokens));
		temp = lst->next;
		free(lst);
		lst = temp;
	}
	free2d(shell->sh_env);
	free(shell->cmdline);
	shell->cmdline = NULL;
	shell->sh_env = NULL;
}

void	free2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
}
