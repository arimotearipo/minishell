/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:21:25 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/15 22:29:20 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
The skipseparator() will read through separators characters and
assign them into the token linked list.
*/
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

/*
The assignquote() function will mutate the value of quotetype and openquote
based on current character.
*/
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

/*
Collect token will append each token into the token linked list.
*/
void	collect(char *line, int *i, t_cmdgroup *cmd, int *start)
{
	if (*i - *start > 0)
		addlist(cmd, line, *start, *i - *start);
	if (ft_strchr(" <>", line[*i]))
		skipseparator(cmd, line, i);
}

/*
Collect token will collect all the tokens. It does this by first
identifying any open quotes and the quote type. The assignquote()
function will manipulate the value of openquote and quotetype.
Upon encountering a '|' it will exit the function. The separation
of tokens is determined by whitespaces and the '<' and '>' and
wheter the said characters is in open quote or not.
*/
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

/*
Trim all the trailing whitespaces around the command line.
Will count how many command groups there are and create a linked lists
of command groups. Then it will collect all token and assigned it in
another linked list inside each node of command group linked list.
*/
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
