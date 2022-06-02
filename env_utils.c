/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:18:11 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/02 18:12:01 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	showenv(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->sh_env[i + 1] != NULL)
	{
		printf("%s\n", shell->sh_env[i]);
		i++;
	}
}

void	clone_env(char **envp, t_shell *shell)
{
	int		i;
	int		j;
	char	*exitvalue;
	char	*exitvar;

	i = 0;
	while (envp[i] != NULL)
		i++;
	i++;
	shell->sh_env = malloc(sizeof(char *) * i + 1);
	j = 0;
	while (j < i - 1)
	{
		shell->sh_env[j] = ft_strdup(envp[j]);
		j++;
	}
	exitvalue = ft_itoa(shell->exit);
	exitvar = ft_strjoin("?=", exitvalue);
	shell->sh_env[j] = ft_strdup(exitvar);
	free(exitvalue);
	free(exitvar);
	shell->sh_env[++j] = NULL;
}

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
