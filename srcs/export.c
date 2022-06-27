/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 01:13:50 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/27 17:31:31 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	removeplus(char **arg)
{
	int	i;

	i = ft_strchri(*arg, 0, '=');
	ft_memmove(&((*arg)[i - 1]), &((*arg)[i]), ft_strlen(*arg) - i + 1);
}

char	*concatenatevalue(t_shell *shell, char *curarg, char *arg)
{
	char	*key;
	char	*joinedvalue;

	(void)shell;
	joinedvalue = ft_strjoin(ft_strchr(curarg, '=') + 1,
			ft_strchr(arg, '=') + 1);
	key = getvarname(curarg);
	strjoinandfree(&key, "=");
	strjoinandfree(&key, joinedvalue);
	free(joinedvalue);
	return (key);
}

void	replacevar(t_shell *shell, char *arg, int index)
{
	int		valid;
	char	*joinedarg;

	valid = ft_strchri(arg, 0, '=');
	if (valid <= 0)
	{
		if (valid == 0)
			printerror(shell, "Error. Argument isn't a valid indentifier\n", 2);
		return ;
	}
	if (shell->exportflag == 1)
	{
		joinedarg = concatenatevalue(shell, shell->sh_env[index], arg);
		free(shell->sh_env[index]);
		shell->sh_env[index] = joinedarg;
		return ;
	}
	free(shell->sh_env[index]);
	shell->sh_env[index] = ft_strdup(arg);
}

/*
The replace var function will take in the whole key=value pair as arg.
It will then use the arg to replace the key=value at index passed as index
in the 2D shell environment array.
*/
// void	replacevar(t_shell *shell, char *arg, int index)
// {
// 	int		valid;

// 	valid = ft_strchri(arg, 0, '=');
// 	if (valid <= 0)
// 	{
// 		if (valid == 0)
// 			printerror(shell, "Error. Argument isn't a valid indentifier\n", 2);
// 		return ;
// 	}
// 	free(shell->sh_env[index]);
// 	shell->sh_env[index] = ft_strdup(arg);
// }

/*
insertvar() will check the validity of the key=value pair that is about
to be passed into the 2D environment array. It will then duplicate another
2D array and copies everything from existing 2D environment array into the
new one while appending arg to the end. The sh_env pointer will then be pointed
to the new 2D array. IT DOES NOT FREE THE STRING PASSED AS arg.
*/
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

void	exe_export(t_shell *shell, t_cmdgroup *grp, t_token *tkn)
{
	t_token	*first;

	(void)grp;
	first = tkn;
	if (tkn->next == NULL)
		showenv(shell, tkn, 0);
	tkn = tkn->next;
	while (tkn != NULL)
	{
		if ((tkn->type == ARG || tkn->type == COMMAND)
			&& cvk(shell, tkn->str, 0))
		{
			if (shell->exportflag == 1)
				removeplus(&(tkn->str));
			find_and_replace(shell, tkn->str);
		}
		shell->exportflag = 0;
		tkn = tkn->next;
	}
	tkn = first;
}
