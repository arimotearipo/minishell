/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:30:32 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/21 22:30:42 by wwan-taj         ###   ########.fr       */
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
	if (shell->sh_env[m] == NULL || m == -1)
		return ;
	new_env = malloc(sizeof(char *) * arrlen);
	i = 0;
	j = 0;
	while (i < arrlen)
	{
		if (j == m)
			j++;
		if (shell->sh_env[j] == NULL)
			break ;
		new_env[i++] = ft_strdup(shell->sh_env[j++]);
	}
	new_env[i] = NULL;
	free2d(shell->sh_env);
	shell->sh_env = new_env;
}

void	exe_unset(t_shell *shell, t_cmdgroup *grp, t_token *tkn)
{
	t_token	*first;

	(void)grp;
	first = tkn;
	tkn = tkn->next;
	while (tkn != NULL)
	{
		if (tkn->type == ARG || tkn->type == COMMAND)
		{
			if (cvk(shell, tkn->str))
				unset(shell, tkn->str);
		}
		tkn = tkn->next;
	}
	tkn = first;
}
