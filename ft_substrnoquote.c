/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substrnoquote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:38:28 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/02 18:15:34 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	assignopeningquote(char const *s, unsigned int *start, int *flag,
	char *openingquote)
{
	if ((s[*start] == '\'' || s[*start] == '\"') && *flag == 0)
	{
		*openingquote = s[*start];
		(*start)++;
		*flag = 1;
	}
}

char	*ft_substrnoquote(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	char	openingquote;
	int		flag;

	openingquote = '\'';
	i = 0;
	flag = 0;
	str = malloc(len + 1);
	while (i < len)
	{
		assignopeningquote(s, &start, &flag, &openingquote);
		while (i < len && !ft_strchr("'\"", s[start]) && flag == 0)
			str[i++] = s[(start)++];
		assignopeningquote(s, &start, &flag, &openingquote);
		while (s[start] != openingquote && i < len && flag == 1)
			str[i++] = s[(start)++];
		flag = 0;
		(start)++;
	}
	str[len] = 0;
	return (str);
}

// int		crosscheck(const char *s1, const char *s2)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (s1[i] != '\0')
// 	{
// 		j = 0;
// 		while (s2[j] != '\0')
// 		{
// 			if (s1[i] == s2[j])
// 				return (1);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int		findnextquote(const char *s, int startindex)
// {
// 	if (crosscheck("'\"", s) == 0)
// 		return (-1);
// 	while (s[startindex] != '\'' && s[startindex] != '\"')
// 		startindex++;
// 	return (startindex);
// }

// char	*ft_substrnoquote(char const *s, unsigned int start, size_t len)
// {
// 	char	*new;
// 	char	*temp;
// 	int		end;

// 	// (void)start;
// 	new = ft_strdup("");
// 	printf("length %ld\n", len);
// 	while (start < len)
// 	{
// 		if (s[start] == '\'' || s[start] == '\"')
// 		{
// 			end = ft_strchri(s, start + 1, s[start]);
// 			temp = ft_substr(s, start + 1, end - start - 1);
// 			start = end;
// 		}
// 		else
// 		{
// 			end = findnextquote(s, start);
// 			temp = ft_substr(s, start, end - start);
// 			start = end;
// 		}
// 		new = ft_strjoin(new, temp);
// 		free(temp);
// 	}
// 	return (new);
// }