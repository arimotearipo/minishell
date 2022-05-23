/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:21:25 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/23 11:12:05 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	t_cmdgroup	*cmd;
	// char		*line;
	char		*line = "hello | world";

	(void)av;
	// cmd.tokens = NULL;
	if (ac == 1)
	{
		while (1)
		{
			// line = readline("minishell>% ");
			if (ft_strncmp(line, "exit", 4) == 0)
				exit(0);
			cmd = collectcmdgroup(line);
			collecttoken(line, cmd);
			add_history(line);
			showlist(cmd);
			clearmemory(cmd);
			break ;
		}
	}
	// system("leaks minishell");
	return (0);
}

t_cmdgroup	*collectcmdgroup(char *line)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '|')
			count++;
		i++;
	}
	return (creategroup(count));
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
		return (-1);
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
		return (-1);
	return (len);
}

int	getlen(char *line, int *i)
{
	int	len;

	len = 0;
	if (line[*i] == '"' || line[*i] == '\'')
		len = getquotedlen(line, line[*i], i);
	else if (line[*i] == '<' || line[*i] == '>')
		len = getredlen(line, line[*i], i);
	else if (line[*i] > 32)
		len = gettokenlen(line, i);
	return (len);
}

int	collecttoken(char *line, t_cmdgroup *cmd)
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
		len = getlen(line, &i);
		if (line[i] == '|')
		{
			cmd = cmd->next;
			i++;
			continue ;
		}
		if (addlist(cmd, line, start, len) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}