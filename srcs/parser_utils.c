/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 00:22:26 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/06/26 00:23:02 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	markemptystr(t_shell *shell, t_token *token)
{
	int	i;

	(void)shell;
	i = 0;
	while (token->str[i] != 0)
	{
		if (!ft_strchr("'\"", token->str[i]))
		{
			token->emptystr = 0;
			return ;
		}
		i++;
	}
	token->emptystr = 1;
}
