/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:12:09 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/06/01 15:01:48 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(t_shell *shell, t_token *token, int *i)
{
	char	*var;
	char	*expandedvar;
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
	var = ft_substr(token->str, start, len);
	env = ft_getenv(shell->sh_env, var);
	free(var);
	if (env == NULL)
		expandedvar = ft_strdup("");
	else
		expandedvar = ft_strdup(env);
	return (expandedvar);
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

void	expandstr(char **new, char **str)
{
	char	*temp;

	temp = *new;
	*new = ft_strjoin(temp, *str);
	free(*str);
	free(temp);
}

void	translate(t_shell *shell, t_token *token)
{
	int		i;
	int		j;
	char	*new;
	char	*var;
	char	*str;

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
		expandstr(&new, &str);
		// temp = new;
		// new = ft_strjoin(temp, str);
		// free(str);
		// free(temp);
		var = get_var(shell, token, &i);
		expandstr(&new, &var);
		// temp = new;
		// new = ft_strjoin(temp, var);
		// free(temp);
		// free(var);
	}
	free(token->str);
	token->str = new;
}

void	handledollar(char *cur, char next, int openquote, char quotetype)
{
	if (*cur != '$')
		return ;
	if (next <= 32 && openquote == 0)
		*cur = '$';
	else if (!ft_strchr("'\" ", next) && next != '\0' && quotetype != '\'')
		*cur = (char)(-36);
	else if (ft_strchr("'\"", next) && openquote == 0)
		*cur = (char)(DOLLARDEL);
}

void	indentifyenv(t_shell *shell, char *str)
{
	int		i;
	int		openquote;
	char 	quotetype;

	(void)shell;
	openquote = 0;
	quotetype = '\"';
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr("'\"", str[i]) && openquote == 0)
		{
			quotetype = str[i];
			openquote = 1;
		}
		else if (str[i] == quotetype && openquote == 1)
			openquote = 0;
		handledollar(&str[i], str[i + 1], openquote, quotetype);
		i++;
	}
}

// void	indentifyenv(t_shell *shell, char *str)
// {
// 	int		i;
// 	int		openquote;
// 	char 	quotetype;

// 	(void)shell;
// 	openquote = 0;
// 	quotetype = '\"';
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (ft_strchr("'\"", str[i]) && openquote == 0)
// 		{
// 			quotetype = str[i];
// 			openquote = 1;
// 		}
// 		else if (str[i] == quotetype && openquote == 1)
// 			openquote = 0;
// 		if (str[i] == '$' && str[i + 1] <= 32 && openquote == 0) // When nothing next to $
// 		{
// 			printf("MASUK?\n");
// 			str[i] = '$';
// 		}
// 		else if (str[i] == '$' && quotetype != '\'' && !ft_strchr("'\" ", str[i + 1]) && str[i + 1] != '\0') // When $ need to be expanded
// 		{
// 			printf("MASUK 1\n");
// 			str[i] = (char)(-36);
// 		}
// 		else if (str[i] == '$' && ft_strchr("'\"", str[i + 1]) && openquote == 0) // When $ needs to be removed
// 		{
// 			printf("MASUK 2\n");
// 			str[i] = (char)(DOLLARDEL);
// 		}
// 		i++;
// 	}
// }

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
				indentifyenv(shell, cmd->tokens->str);
				translate(shell, cmd->tokens);
			}
			stripquote(shell, cmd->tokens);
			cmd->tokens = cmd->tokens->next;
		}
		cmd->tokens = firsttoken;
		cmd = cmd->next;
	}
}