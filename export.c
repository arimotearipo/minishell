/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 01:13:50 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/08 20:16:30 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replacevar(t_shell *shell, char *arg, int i)
{
	int	valid;
	
	valid = ft_strchri(arg, 0, '=');
	if (valid <= 0)
	{
		if (valid == 0)
			printerror(shell, "Error. Argument is not a valid indentifier\n", 2);
		return ;
	}
	free(shell->sh_env[i]);
	shell->sh_env[i] = ft_strdup(arg);
}

void	export(t_shell *shell, char *arg)
{
	char	**new_env;
	int		valid;
	int		count;
	int		i;

	valid = ft_strchri(arg, 0, '=');
	if (valid <= 0)
	{
		if (valid == 0)
			printerror(shell, "Error. Argument is not a valid indentifier\n", 2);
		return ;
	}
	count = ft_2darrlen(shell->sh_env);
	new_env = malloc(sizeof(char *) * (count + 2));
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(shell->sh_env[i]);
		i++;
	}
	new_env[i] = ft_strdup(arg);
	new_env[++i] = NULL;
	free2d(shell->sh_env);
	shell->sh_env = new_env;
}

int		isexisting(t_shell *shell, char *arg)
{
	int		i;
	int		index;

	index = ft_strchri(arg, 0, '=');
	i = 0;
	while (shell->sh_env[i] != NULL)
	{
		if (!ft_strncmp(shell->sh_env[i], arg, index))
			return (i);
		i++;
	}
	return (-1);
}

void	exe_export(t_shell *shell, t_cmdgroup *grp)
{
	t_token	*first;
	int		i;

	first = grp->tokens;
	grp->tokens = grp->tokens->next;
	while (grp->tokens != NULL && grp->tokens->type == ARG)
	{
		i = isexisting(shell, grp->tokens->str);
		if (i >= 0)
			replacevar(shell, grp->tokens->str, i);
		else
			export(shell, grp->tokens->str);
		grp->tokens = grp->tokens->next;
	}
	grp->tokens = first;
}
