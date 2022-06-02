/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:21:25 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/02 18:10:13 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skipseparator(t_cmdgroup *cmd, char *line, int *i)
{
	char	redirection;
	int		len;
	int		start;

	while (ft_strchr("<> ", line[*i]) && line[*i])
	{
		if (ft_strchr("<>", line[*i]))
		{
			len = 0;
			start = *i;
			redirection = line[*i];
			while (line[*i] == redirection)
			{
				(*i)++;
				len++;
			}
			addlist(cmd, line, start, len);
			continue ;
		}
		(*i)++;
	}
}

void	assignquote(char *line, int *i, char *quotetype, int *openquote)
{
	if ((line[*i] == '\'' || line[*i] == '\"') && *openquote == 0)
	{
		*openquote = 1;
		*quotetype = line[*i];
	}
	else if (line[*i] == *quotetype)
		*openquote = 0;
}

void	collect(char *line, int *i, t_cmdgroup *cmd, int *start)
{
	if (*i - *start > 0)
		addlist(cmd, line, *start, *i - *start);
	if (ft_strchr(" <>", line[*i]))
		skipseparator(cmd, line, i);
}

int	collecttoken(char *line, t_cmdgroup *cmd, int *i)
{
	int		openquote;
	char	quotetype;
	int		start;

	start = *i;
	openquote = 0;
	while (line[*i] != '\0')
	{
		assignquote(line, i, &quotetype, &openquote);
		if (line[*i] == '|' && openquote == 0)
		{
			collect(line, i, cmd, &start);
			(*i)++;
			return (1);
		}
		if (ft_strchr(" <>", line[*i]) && openquote == 0)
		{
			collect(line, i, cmd, &start);
			start = *i;
			continue ;
		}
		(*i)++;
	}
	collect(line, i, cmd, &start);
	return (0);
}

void	lexer(char *line, t_shell *shell)
{
	int			i;
	t_cmdgroup	*first;

	i = 0;
	shell->cmdline = ft_strtrim(line, " ");
	free(line);
	shell->cmdgrpcount = countcmdgroups(shell->cmdline);
	creategroup(&(shell->cmdgroup), shell->cmdgrpcount);
	first = shell->cmdgroup;
	while (collecttoken(shell->cmdline, shell->cmdgroup, &i) == 1)
		shell->cmdgroup = shell->cmdgroup->next;
	shell->cmdgroup = first;
}
