/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:34:31 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/11 22:02:31 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*loadbuffer(char *buffer, int fd, char *leftover)
{
	int	numbytes;
	char	*temp;
	
	numbytes = 1;
	while (numbytes)
	{
		numbytes = read(fd, buffer, BUFFER_SIZE);
		// printf("numbytes: %d\n", numbytes);
		if (numbytes == 0)
			return (leftover);
		else if (numbytes < 0)
			return (NULL);
		buffer[numbytes] = '\0';
		if (!leftover)
			leftover = ft_strdup("");
		temp = leftover;
		leftover = ft_strjoin(temp, buffer);
		// printf("loadbuffer: %s\n", leftover);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	// printf("leftover: %s", leftover);
	return (leftover);
}

char	*firstline(char	*text)
{
	int 	i;
	char	*line;

	i = 0;
	while (text[i] != '\n' && text[i] != '\0')
		i++;
	// printf("VALUE OF i: %d\n", i);
	line = ft_substr(text, 0, i + 1);
	return (line);
}

char	*cutoff(char	*leftover)
{
	int 	i;
	char	*temp;
	int		len;

	len = ft_strlen(leftover);
	i = 0;
	while (leftover[i] != '\n' && leftover[i] != '\0')
		i++;
	temp = ft_substr(leftover, i + 1, len - 1);
	if (temp[0] == '\0')
		return (NULL);
	// printf("i + 1: %c\n", leftover[i + 1]);
	// printf("temp: %s\n", temp);
	free(leftover);
	return (temp);
}

char	*get_next_line(int fd)
{
	char				*buffer;
	char				*text;
	static	char		*leftover;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	// printf("First leftover: %s\n", leftover);
	if (!leftover)
	{
		// printf("there is no leftover\n");
		leftover = ft_strdup("");
	}
	text = loadbuffer(buffer, fd, leftover);
	// printf("text: %s\n", text);
	free(buffer);
	buffer = NULL;
	if (!text)
		return (NULL);
	// printf("Last leftover: %s\n", leftover);
	leftover = cutoff(text);
	return (firstline(text));
}

// int	main(void)
// {
// 	int	fd;
// 	char	*line;

// 	fd = open("ten.txt", O_RDONLY);
// 	for (int i = 0; i < 19; i++)
// 	{
// 		//printf("--FUNCTION CALL NO %d--\n", i);
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 		line = NULL;
// 	}
// 	return (0);
// }
