/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:17:46 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/22 23:06:21 by wwan-taj         ###   ########.fr       */
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

/*
This function is called upon encountering a '$' sign in the token which 
marks the possibility of expansion. It will determine whether it needs
to expand / not expand / completely remove the '$' sign based on what
the next character, whether it is in a quote and what quote type it is in.
*/
void	handledollar(char *cur, char next, int openquote, char quotetype)
{
	(void)quotetype;
	if (*cur != '$')
		return ;
	if (next <= 32 && openquote == 0)
		*cur = '$';
	else if (!ft_strchr("'\" ", next) && next != '\0' && openquote == 0)
		*cur = (char)(-36);
	else if (!ft_strchr("'\" ", next) && next != '\0' && openquote == 1
		&& quotetype == '"')
		*cur = (char)(-36);
	else if (ft_strchr("'\"", next) && openquote == 0)
		*cur = (char)(DOLLARDEL);
}

/*
This function will mark the the quotes that are wrapping the envinronment
values that will be expanded. It does this by marking the character if
it's negative value. Therefore, the quotes will be treated as a non-quote
and will not be removed later in the stripquote function
*/
void	markquote(char **var, int quote1, int quote2)
{
	int	i;

	i = 0;
	while ((*var)[i] != '\0')
	{
		if ((*var)[i] == quote1 || (*var)[i] == quote2)
			(*var)[i] = ((char)(*var)[i]) * -1;
		i++;
	}
}
