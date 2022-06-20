/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:26:21 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/06/20 14:39:12 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strjoinandfree(char **new, char *str)
{
	char	*temp;

	temp = *new;
	*new = ft_strjoin(temp, str);
	free(temp);
}

void	isechooption(t_token **tokens, int *option)
{
	int	i;

	while ((*tokens)->type != ARG)
		*tokens = (*tokens)->next;
	while (*tokens != NULL && !ft_strncmp("-n", (*tokens)->str, 2))
	{
		i = 2;
		while ((*tokens)->str[i] == 'n')
			i++;
		if ((*tokens)->str[i] == '\0')
		{
			*option = 1;
			*tokens = (*tokens)->next;
		}
		else
			break ;
	}
}

int	exe_echo(t_shell *shell, t_cmdgroup *cmd, t_token *token)
{
	t_token	*tokens;
	int		option;

	(void)shell;
	option = 0;
	tokens = token->next;
	cmd->topass = ft_strdup("");
	if (tokens != NULL)
		isechooption(&tokens, &option);
	while (tokens != NULL)
	{
		if (tokens->type == ARG)
		{
			if (ft_strcmp(cmd->topass, ""))
				strjoinandfree(&(cmd->topass), " ");
			strjoinandfree(&(cmd->topass), tokens->str);
		}
		tokens = tokens->next;
	}
	if (option == 0)
		strjoinandfree(&(cmd->topass), "\n");
	ft_putstr_fd(cmd->topass, STDOUT);
	free(cmd->topass);
	return (0);
}
