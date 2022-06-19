/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:18:11 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/20 02:15:36 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
showenv() function will show all the variables in the 2D environment array.
The arg option shall be either 0 or 1. When 1 is passed as option, the env
displayed will be preceded by "declare -x " whereas when 1 is passed as option,
the env will be displayed normally.
*/
void	showenv(t_shell *shell, t_token *token, int arg)
{
	int	i;
	int	m;
	int	len;

	if (token->next != NULL)
	{
		printerror(shell, "Error. No such file or directory\n", NOCOMMAND);
		return ;
	}
	m = getvarindex(shell, "_");
	if (m == -1)
		insertvar(shell, "_=env");
	else
		replacevar(shell, "_=env", m);
	len = ft_2darrlen(shell->sh_env);
	i = 0;
	while (i < len - 1)
	{
		if (!ft_strcchr(shell->sh_env[i], "?", '='))
			i++;
		if (!arg)
			printf("declare -x ");
		printf("%s\n", shell->sh_env[i]);
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
	if (getvarindex(shell, "?"))
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
the key of the variable (before the '=' sign).
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

/*
Returns a malloc string that contains the 'key' of the variable. The malloced
string is from the beginning until right before the '=' sign in the 2D shell
env array. The argument 'str' is a the complete key=value pair.
*/
char	*getvarname(char *str)
{
	int		i;
	char	*varname;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	varname = ft_substr(str, 0, i);
	return (varname);
}

// Will return the index of the variable in the sh_env specified by arg
// The string passed as arg should not include the '=' sign. Upon success,
// getvarindex() will return the index of the var and -1 upon failure.
int	getvarindex(t_shell *shell, char *arg)
{
	int	m;

	m = 0;
	while (shell->sh_env[m] != NULL)
	{
		if (!ft_strcchr(shell->sh_env[m], arg, '='))
			return (m);
		m++;
	}
	return (-1);
}
