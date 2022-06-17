/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:35:51 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/17 19:51:24 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_varinheredoc(t_shell *shell, char *str, int *i)
{
	char	*var;
	char	*expandedvar;
	int		len;
	int		start;
	char	*env;

	len = 0;
	start = ++(*i);
	while (!ft_strchr("'\"$=/ ", str[*i]) && str[*i])
	{
		len++;
		(*i)++;
	}
	var = ft_substr(str, start, len);
	env = ft_getenv(shell->sh_env, var);
	free(var);
	if (env == NULL)
		expandedvar = ft_strdup("");
	else
		expandedvar = ft_strdup(env);
	return (expandedvar);
}

char	*translateinheredoc2(char *new, char *toexpand, int *j, int *i)
{
	char	*str;

	str = ft_substr(toexpand, *j, *i - *j);
	expandstr(&new, &str);
	str = ft_strdup("$");
	expandstr(&new, &str);
	(*i)++;
	return (new);
}

void	translateinheredoc(t_shell *shell, char **toexpand)
{
	int		i;
	int		j;
	char	*new;
	char	*var;
	char	*str;

	i = 0;
	j = 0;
	new = ft_strdup("");
	while ((*toexpand)[i])
	{
		j = i;
		while ((*toexpand)[i] != '$' && (*toexpand)[i])
			i++;
		if (ft_strchr("'\"=/\\ ", (*toexpand)[i + 1]))
		{
			new = translateinheredoc2(new, *toexpand, &j, &i);
			continue ;
		}
		str = ft_substr(*toexpand, j, i - j);
		expandstr(&new, &str);
		var = get_varinheredoc(shell, *toexpand, &i);
		expandstr(&new, &var);
	}
	*toexpand = new;
}
