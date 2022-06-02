/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:17:46 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/02 18:18:24 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	searchdollarsign(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == -36 || str[i] == DOLLARDEL)
			return (1);
		i++;
	}
	return (0);
}

void	expandstr(char **new, char **str)
{
	char	*temp;

	temp = *new;
	*new = ft_strjoin(temp, *str);
	free(*str);
	free(temp);
}

void	handledollar(char *cur, char next, int openquote, char quotetype)
{
	if (*cur != '$')
		return ;
	if (next <= 32 && openquote == 0)
		*cur = '$';
	else if (!ft_strchr("'\" ", next) && next != '\0' && quotetype != '\'')
		*cur = (char)(-36);
	else if (ft_strchr("'\"", next) && openquote == 0)
		*cur = (char)(DOLLARDEL);
}
