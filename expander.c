/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:12:09 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/05/29 19:06:57 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(t_shell *shell, t_token *token, int *i)
{
	char	*var;
	char	*new;
	int		j;

	j = 0;
	len =
	var = malloc(len + 1);
	while((token->str[*i] != '$' || token->str[*i] != -36) && token->str[*i])
	{
		var[j] = token->str[*i + j];
		(*i)++;
		j++;
	}
	var[j] = 0;
	new = ft_strdup(ft_getenv(shell->sh_env, var));
	return (new);
}

void	translate(t_shell *shell, t_token *token)
{
	int		i;
	int		j;
	char	*new;
	char	*var;
	char	*str;

	i = 0;
	new = "";
	while (token->str[i])
	{
		j = i;
		while (token->str[i] != -36 && token->str[i])
			i++;
		str = ft_substr(token->str, j, i - j);
		new = ft_strjoin(new, str);
		free(str);
		var = get_var(shell, token, &i);
		new = ft_strjoin(new, var);
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