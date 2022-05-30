/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:12:09 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/05/30 16:07:18 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(t_shell *shell, t_token *token, int *i)
{
	char	*var;
	char	*new;
	int		len;
	int		start;
	char	*env;

	len = 0;
	start = ++(*i);
	while(!ft_strchr("'\"$", token->str[*i]) && token->str[*i] != -36
		&& token->str[*i])
	{
		len++;
		(*i)++;
	}
	// len = strchri(token->str, *i, '=');
	var = ft_substr(token->str, start, len);
	env = ft_getenv(shell->sh_env, var);
	if (env == NULL)
		new = ft_strdup("");
	else
		new = ft_strdup(env);
	free(var);
	return (new);
}

void	translate(t_shell *shell, t_token *token)
{
	int		i;
	int		j;
	char	*new;
	char	*var;
	char	*str;
	char	*temp;

	i = 0;
	new = ft_strdup("");
	while (token->str[i])
	{
		j = i;
		while (token->str[i] != -36 && token->str[i])
			i++;
		str = ft_substr(token->str, j, i - j);
		temp = new;
		new = ft_strjoin(temp, str);
		free(str);
		free(temp);
		var = get_var(shell, token, &i);
		temp = new;
		new = ft_strjoin(temp, var);
		free(temp);
		free(var);
	}
	free(token->str);
	token->str = new;
}

void	expand(t_shell *shell)
{
	t_cmdgroup	*cmd;
	t_token		*firsttoken;
	
	cmd = shell->cmdgroup;
	while (cmd != NULL)
	{
		firsttoken = cmd->tokens;
		while (cmd->tokens != NULL)
		{
			if (cmd->tokens->type == ARG)
				translate(shell, cmd->tokens);
			cmd->tokens = cmd->tokens->next;
		}
		cmd->tokens = firsttoken;
		cmd = cmd->next;
	}
}