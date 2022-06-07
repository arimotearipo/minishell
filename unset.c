/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:30:32 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/08 01:50:53 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_shell *shell, char *arg)
{
	int		m;
	int		i;
	int		j;
	int		arrlen;
	char	**new_env;

	arrlen = ft_2darrlen(shell->sh_env);
	m = 0;
	while (m < arrlen)
	{
		if (!ft_strcchr(shell->sh_env[m], arg, '='))
			break ;
		m++;
	}
	// printf("arrlen: %d m: %d\n", arrlen, m);
	new_env = malloc(sizeof(char *) * arrlen);
	i = 0;
	j = 0;
	while (i < arrlen)
	{
		if (j == m)
			j++;
		if (shell->sh_env[j] != NULL)
			new_env[i] = ft_strdup(shell->sh_env[j]);
		i++;
		j++;
	}
	new_env[i] = NULL;
	free2d(shell->sh_env);
	shell->sh_env = new_env;
}
