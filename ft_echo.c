/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:26:21 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/06/02 20:26:35 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_shell *shell, t_cmdgroup *cmd)
{
	t_token	*tokens;
	int		option;

	(void)shell;
	option = 0;
	tokens = cmd->tokens;
	tokens = tokens->next;
	if (ft_strcmp("-n", tokens->str))
	{
		option = 1;
		tokens = tokens->next;
	}
	while (tokens->type == ARG)
	{
		ft_putstr_fd(tokens->str, 1);
		tokens = tokens->next;
	}
	if (option == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}