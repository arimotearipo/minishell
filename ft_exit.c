/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:19:43 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/06/08 14:49:11 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strisnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_shell *shell, t_cmdgroup *cmd)
{
	t_token	*tokens;

	tokens = cmd->tokens->next;
	if (tokens != NULL && tokens->next != NULL)
	{
		printerror(shell, "bash: exit: too many arguments\n", 1);
	}
	else if (tokens != NULL)
	{
		if (ft_strisnum(tokens->str) == 0)
		{
			printerror(shell, "bash: exit: a: numeric argument required\n", 1);
			exit(255);
		}
		else
			exit(ft_atoi(tokens->str));
	}
	else
		exit(0);
	return (0);
}
