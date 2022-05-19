/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:21:25 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/19 18:23:54 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	t_cmd	cmd;
	char	*line;

	(void)av;
	if (ac == 1)
	{
		while (1)
		{
			line = readline("minishell>% ");
			collecttoken(line, &cmd);
			add_history(line);
			while (cmd.tokens != NULL)
			{
				printf("%s\n", cmd.tokens->str);
				cmd.tokens = cmd.tokens->next;
			}
			clearmemory(&cmd);
		}
	}
	return (0);
}

int	getquotedlen(char *line, char c, int *i)
{
	int	len;

	len = 2;
	(*i)++;
	while (line[*i] != c && line[*i] != '\0')
	{
		*i += 1;
		len++;
	}
	if (line[*i] == '\'' || line[*i] == '"')
		(*i)++;
	else
	{
		printerror();
		return (-1);
	}
	return (len);
}

int	gettokenlen(char *line, int *i)
{
	int	len;

	len = 0;
	while (line[*i] != ' ' && line[*i] != '"'
		&& line[*i] != '\'' && line[*i] != '\0'
		&& line[*i] != '<' && line[*i] != '>'
		&& line[*i] != '|')
	{
		(*i)++;
		len++;
	}
	return (len);
}

int	getredlen(char *line, char c, int *i)
{
	int	len;

	len = 0;
	while (line[*i] == c)
	{
		(*i)++;
		len++;
	}
	if ((c == '<' || c == '>') && len > 2)
	{	
		printerror();
		return (-1);
	}
	else if (c == '|' && len > 1)
	{
		printerror();
		return (-1);
	}
	return (len);
}

void	collecttoken(char	*line, t_cmd *cmd)
{
	int		i;
	int		len;
	int		start;

	i = 0;
	start = 0;
	while (line[i] != '\0')
	{
		start = i;
		if (line[i] <= 32)
		{
			i++;
			continue ;
		}
		else if (line[i] == '"' || line[i] == '\'')
			len = getquotedlen(line, line[i], &i);
		else if (line[i] == 124 || line[i] == 60 || line[i] == 62)
			len = getredlen(line, line[i], &i);
		else if (line[i] > 32)
			len = gettokenlen(line, &i);
		filllst(&(cmd->tokens), line, start, len);
	}
}
