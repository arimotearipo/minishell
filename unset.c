/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:30:32 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/08 14:47:42 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_shell *shell, char *arg)
{
	int		arrlen;
	int		m;
	int		i;
	int		j;
	char	**new_env;

	arrlen = ft_2darrlen(shell->sh_env);
	m = getvarindex(shell, arg);
	new_env = malloc(sizeof(char *) * arrlen);
	i = 0;
	j = 0;
	while (i < arrlen)
	{
		if (j == m)
			j++;
		if (shell->sh_env[j] == NULL)
			break ;
		new_env[i] = ft_strdup(shell->sh_env[j]);
		i++;
		j++;
	}
	new_env[i] = NULL;
	free2d(shell->sh_env);
	shell->sh_env = new_env;
}

void	exe_unset(t_shell *shell, t_cmdgroup *grp)
{
	t_token	*first;

	first = grp->tokens;
	grp->tokens = grp->tokens->next;
	while (grp->tokens != NULL && grp->tokens->type == ARG)
	{
		unset(shell, grp->tokens->str);
		grp->tokens = grp->tokens->next;
	}
	grp->tokens = first;
}
