/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:18:11 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/30 16:18:20 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clone_env(char **envp, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i] != NULL)
		i++;
	shell->sh_env = malloc(sizeof(char *) * i + 1);
	j = 0;
	while (j < i)
	{
		shell->sh_env[j] = ft_strdup(envp[j]);
		j++;
	}
	shell->sh_env[j] = NULL;
}