/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:26:21 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/06/07 16:24:18 by mahmad-j         ###   ########.fr       */
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

int	ft_echo(t_shell *shell, t_cmdgroup *cmd)
{
	t_token	*tokens;
	int		option;

	(void)shell;
	option = 0;
	tokens = cmd->tokens->next;
	cmd->topass = ft_strdup("");
	isechooption(&tokens, &option);
	while (tokens != NULL && tokens->type == ARG)
	{
		strjoinandfree(&(cmd->topass), tokens->str);
		if (tokens->next != NULL && tokens->next->type == ARG)
			strjoinandfree(&(cmd->topass), " ");
		tokens = tokens->next;
	}
	if (option == 0)
		strjoinandfree(&(cmd->topass), "\n");
	printf("(%s)", cmd->topass);
	free(cmd->topass);
	return (0);
}
