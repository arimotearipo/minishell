/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlength.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:02:09 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/25 13:49:20 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getquotedlen(char *line, char c, int *i, int *len)
{
	(*i)++;
	while (line[*i] != c && line[*i] != '\0')
	{
		*i += 1;
		(*len)++;
	}
	if (line[*i] == c)
		(*i)++;
	else
		return (-1);
	if (line[*i] == c)
		getquotedlen(line, c, i, len);
	return (*len);
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
	{
		len = 2;
		len = getquotedlen(line, line[*i], i, &len);
	}
	else if (line[*i] == '<' || line[*i] == '>')
		len = getredlen(line, line[*i], i);
	else if (line[*i] > 32)
		len = gettokenlen(line, i);
	return (len);
}