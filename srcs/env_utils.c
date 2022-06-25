/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:18:11 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/26 00:36:56 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_no_arg(char *arg)
{
	char	*varkey;
	char	*varvalue;

	varkey = getvarname(arg);
	varvalue = ft_strchr(arg, '=') + 1;
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(varkey, 1);
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(varvalue, 1);
	ft_putendl_fd("\"", 1);
	free(varkey);
}

void    find_and_replace(t_shell *shell, char *arg)
{
	int        m;
	char    *key;

	key = getvarname(arg);
	m = getvarindex(shell, key);
	free(key);
	if (m == -1)
		insertvar(shell, arg);
	else
		replacevar(shell, arg, m);
}

/*
showenv() function will show all the variables in the 2D environment array.
The arg option shall be either 0 or 1. When 1 is passed as option, the env
displayed will be preceded by "declare -x " whereas when 1 is passed as option,
the env will be displayed normally.
*/
void	showenv(t_shell *shell, t_token *token, int arg)
{
	int	i;
	int	len;

	if (token->next != NULL)
	{
		printerror(shell, "Error. No such file or directory\n", NOCOMMAND);
		return ;
	}
	find_and_replace(shell, "_=/usr/bin/env");
	len = ft_2darrlen(shell->sh_env);
	i = 0;
	while (i < len - 1)
	{
		if (!ft_strcchr(shell->sh_env[i], "?", '='))
			i++;
		if (!arg)
			export_no_arg(shell->sh_env[i]);
		else
			ft_putendl_fd(shell->sh_env[i], 1);
		i++;
	}
}

// Will duplicate the environment pointer that was received from the main()
// function and add a secret env variable which is the exit value that is
// represented by the '?' key.
void	clone_env(char **envp, t_shell *shell)
{
	int		i;
	int		j;
	char	*exitvalue;
	char	*exitvar;

	i = ft_2darrlen(envp) + 1;
	shell->sh_env = malloc(sizeof(char *) * i + 1);
	j = -1;
	while (++j < i - 1)
		shell->sh_env[j] = ft_strdup(envp[j]);
	if (getvarindex(shell, "?") != -1)
		updateexitvalue(shell);
	else
	{
		exitvalue = ft_itoa(shell->exit);
		exitvar = ft_strjoin("?=", exitvalue);
		shell->sh_env[j] = ft_strdup(exitvar);
		free(exitvalue);
		free(exitvar);
		shell->sh_env[++j] = NULL;
	}
}

/*
Will retrieve the pointer next to the '=' sign in the 2D shell env array.
The return value do not need to be freed. The 'var' argument passed is 
the key of the variable (before the '=' sign). The function will return
the value of the variable.
*/
char	*ft_getenv(char **env, char *var)
{
	int		i;
	char	*pointer;

	i = 0;
	while (env[i] != NULL && ft_strcchr(env[i], var, '=') != 0)
	{
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	pointer = ft_strchr(env[i], '=');
	return (pointer + 1);
}
