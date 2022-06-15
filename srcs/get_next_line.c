/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:33:10 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/12 16:12:44 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*loadbuffer(int fd, char *initbuf, char *buffer)
{
	int		numbytes;
	char	*temp;

	numbytes = 1;
	while (numbytes != '\0')
	{
		numbytes = read(fd, initbuf, BUFFER_SIZE);
		if (numbytes == 0)
			return (buffer);
		else if (numbytes < 0)
			return (NULL);
		initbuf[numbytes] = '\0';
		if (!buffer)
			buffer = ft_strdup("");
		temp = buffer;
		buffer = ft_strjoin(temp, initbuf);
		free(temp);
		temp = NULL;
		if (ft_strchr(initbuf, '\n'))
			break ;
	}
	return (buffer);
}

char	*splittext(char	*text)
{
	int		i;
	char	*buffer;

	i = 0;
	while (text[i] != '\0' && text[i] != '\n')
		i++;
	buffer = ft_substr(text, i + 1, ft_strlen(text) - i);
	if (buffer[0] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	text[i + 1] = '\0';
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*text;
	char		*initbuf;
	static char	*buffer[5000];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	initbuf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!initbuf)
		return (NULL);
	text = loadbuffer(fd, initbuf, buffer[fd]);
	free(initbuf);
	initbuf = NULL;
	if (!text)
		return (NULL);
	buffer[fd] = splittext(text);
	return (text);
}
