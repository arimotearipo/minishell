/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:26:21 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/06/27 18:25:35 by wwan-taj         ###   ########.fr       */
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

void	isechooption(t_cmdgroup *cmd, t_token **tokens, int *option)
{
	int	i;

	while ((*tokens)->type != ARG || (!ft_strcmp((*tokens)->str, "")
			&& (*tokens)->emptystr == 0))
	{
		*tokens = (*tokens)->next;
		if (*tokens == NULL)
			break ;
	}
	if (*tokens != NULL && !ft_strcmp((*tokens)->str, "")
		&& (*tokens)->emptystr == 1)
			cmd->todelete = 1;
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

void	printtopass(t_cmdgroup *cmd)
{
	if (cmd->todelete == 1)
		ft_memmove(cmd->topass, cmd->topass + 1, ft_strlen(cmd->topass));
	ft_putstr_fd(cmd->topass, STDOUT);
	free(cmd->topass);
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
		isechooption(cmd, &tokens, &option);
	while (tokens != NULL)
	{
		if (tokens->type == ARG)
		{
			if ((ft_strcmp(cmd->topass, "") && ft_strcmp(tokens->str, ""))
				|| (!ft_strcmp(tokens->str, "") && tokens->emptystr == 1))
				strjoinandfree(&(cmd->topass), " ");
			strjoinandfree(&(cmd->topass), tokens->str);
		}
		tokens = tokens->next;
	}
	if (option == 0)
		strjoinandfree(&(cmd->topass), "\n");
	printtopass(cmd);
	return (0);
}
