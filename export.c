/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 01:13:50 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/11 20:48:57 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replacevar(t_shell *shell, char *arg, int index)
{
	int		valid;

	valid = ft_strchri(arg, 0, '=');
	if (valid <= 0)
	{
		if (valid == 0)
			printerror(shell, "Error. Argument isn't a valid indentifier\n", 2);
		return ;
	}
	free(shell->sh_env[index]);
	shell->sh_env[index] = ft_strdup(arg);
}

void	insertvar(t_shell *shell, char *arg)
{
	char	**new_env;
	int		valid;
	int		count;
	int		i;

	valid = ft_strchri(arg, 0, '=');
	if (valid <= 0)
	{
		if (valid == 0)
			printerror(shell, "Error. Argument isn't a valid indentifier\n", 2);
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
	int		i;

	first = grp->tokens;
	grp->tokens = grp->tokens->next;
	while (grp->tokens != NULL && grp->tokens->type == ARG)
	{
		i = isexisting(shell, grp->tokens->str);
		if (i >= 0)
			replacevar(shell, grp->tokens->str, i);
		else
			insertvar(shell, grp->tokens->str);
		grp->tokens = grp->tokens->next;
	}
	grp->tokens = first;
}
