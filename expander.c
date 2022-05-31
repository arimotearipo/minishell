/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:12:09 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/05/31 21:34:46 by wwan-taj         ###   ########.fr       */
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

int	searchdollarsign(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == -36 || str[i] == DOLLARDEL)
			return (1);
		i++;
	}
	return (0);
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
	j = 0;
	if (!searchdollarsign(token->str))
		return ;
	new = ft_strdup("");
	while (token->str[i])
	{
		j = i;
		while ((token->str[i] != -36 && token->str[i] != -1) && token->str[i])
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

void	indentifyenv(t_shell *shell, t_token *token)
{
	int		i;
	int		openquote;
	char 	quotetype;

	(void)shell;
	openquote = 0;
	quotetype = '\"';
	i = 0;
	while (token->str[i] != '\0')
	{
		if (ft_strchr("'\"", token->str[i]) && openquote == 0)
		{
			quotetype = token->str[i];
			openquote = 1;
		}
		else if (token->str[i] == quotetype && openquote == 1)
			openquote = 0;
		
		if (token->str[i] == '$' && quotetype != '\'' 
			&& (!ft_strchr("'\" ", token->str[i + 1])
				&& token->str[i + 1] != '\0'))
		{
			token->str[i] = (char)(-36);
		}
		if (token->str[i] == '$' && ft_strchr("'\"", token->str[i + 1])
			&& openquote == 0)
			{
				token->str[i] = (char)(DOLLARDEL);
			}
		i++;
	}
}

void	stripquote(t_shell *shell, t_token *token)
{
	int	len;
	int	i;
	char	*newstr;

	(void)shell;
	i = 0;
	len = getlen(token->str, &i);
	newstr = ft_substrnoquote(token->str, 0, len);
	free(token->str);
	token->str = newstr;
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
			if (cmd->tokens->type == ARG || cmd->tokens->type == FD)
			{
				indentifyenv(shell, cmd->tokens);
				translate(shell, cmd->tokens);
			}
			stripquote(shell, cmd->tokens);
			cmd->tokens = cmd->tokens->next;
		}
		cmd->tokens = firsttoken;
		cmd = cmd->next;
	}
}