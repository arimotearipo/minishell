/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 01:13:50 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/11 00:14:54 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replacevar(t_shell *shell, char *arg)
{
	int		valid;
	char	*var;
	int		index;

	valid = ft_strchri(arg, 0, '=');
	var = ft_substr(arg, 0, ft_strchri(arg, 0, '='));
	index = getvarindex(shell, var);
	free(var);
	if (valid <= 0 || index < 0)
	{
		if (valid == 0)
			printerror(shell, "Error. Argument is not a valid indentifier\n", 2);
		return (0);
	}
	free(shell->sh_env[index]);
	shell->sh_env[index] = ft_strdup(arg);
	return (1);
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

// Will check whether the arg argument passed is an already existing variable
// in the 2D shell environment. The string passed in arg is the full argument
// that includes the '=' sign and the value of the variable
// It will return the index of the var if it is
// found, it will return -1 if it is not found.
// This function may obsolete as getvarindex does almost the same thing.
int	isexisting(t_shell *shell, char *arg)
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

	first = grp->tokens;
	grp->tokens = grp->tokens->next;
	while (grp->tokens != NULL && grp->tokens->type == ARG)
	{
		if (replacevar(shell, grp->tokens->str) == 0)
			export(shell, grp->tokens->str);
		// i = isexisting(shell, grp->tokens->str);
		// if (i >= 0)
		// 	replacevar(shell, grp->tokens->str, i);
		// else
		// 	export(shell, grp->tokens->str);
		grp->tokens = grp->tokens->next;
	}
	grp->tokens = first;
}
