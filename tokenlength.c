/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlength.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:02:09 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/29 19:28:26 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	getquotedlen(char *line, char c, int *i)
// {
// 	int	len;

// 	len = 2;
// 	(*i)++;
// 	while (line[*i] != c && line[*i] != '\0')
// 	{
// 		*i += 1;
// 		len++;
// 	}
// 	if (line[*i] == '\'' || line[*i] == '"')
// 		(*i)++;
// 	else
// 		return (-1);
// 	return (len);
// }

// int	gettokenlen(char *line, int *i)
// {
// 	int	len;

// 	len = 0;
// 	while (line[*i] != ' ' && line[*i] != '"'
// 		&& line[*i] != '\'' && line[*i] != '\0'
// 		&& line[*i] != '<' && line[*i] != '>'
// 		&& line[*i] != '|')
// 	{
// 		(*i)++;
// 		len++;
// 	}
// 	return (len);
// }

// int	getredlen(char *line, char c, int *i)
// {
// 	int	len;

// 	len = 0;
// 	while (line[*i] == c)
// 	{
// 		(*i)++;
// 		len++;
// 	}
// 	if ((c == '<' || c == '>') && len > 2)
// 		return (-1);
// 	return (len);
// }

// int	getlen(char *line, int *i)
// {
// 	int	len;

// 	len = 0;
// 	if (line[*i] == '"' || line[*i] == '\'')
// 		len = getquotedlen(line, line[*i], i);
// 	else if (line[*i] == '<' || line[*i] == '>')
// 		len = getredlen(line, line[*i], i);
// 	else if (line[*i] > 32)
// 		len = gettokenlen(line, i);
// 	return (len);
// }

int	getquotedlen(char *line, char c, int *i, int *len)
{
	(*i)++;
	while (line[*i] != c && line[*i] != '\0')
	{
		if (c == '\"' && line[*i] == '$')
			line[*i] = (char)(-line[*i]);
		*i += 1;
		(*len)++;
	}
	if (line[*i] == c)
		(*i)++;
	else
		return (-1);
	while (line[*i] > 32 && line[*i] != '<' && line[*i] != '>'
		&& line[*i] != '|')
		*len += gettokenlen(line, i);
	return (*len);
}

int	gettokenlen(char *line, int *i)
{
	int	len;
	int	c;

	len = 0;
	while (line[*i] != ' ' && line[*i] != '"'
		&& line[*i] != '\'' && line[*i] != '\0'
		&& line[*i] != '<' && line[*i] != '>'
		&& line[*i] != '|')
	{
		if(line[*i] == '$')
			line[*i] = (char)(-line[*i]);
		(*i)++;
		len++;
	}
	if (line[*i] == '"' || line[*i] == '\'')
	{
		c = line[*i];
		if (getquotedlen(line, c, i, &len) == -1)
			return (-1);
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
		len = getquotedlen(line, line[*i], i, &len);
	else if (line[*i] == '<' || line[*i] == '>')
		len = getredlen(line, line[*i], i);
	else if (line[*i] > 32)
		len = gettokenlen(line, i);
	return (len);
}
