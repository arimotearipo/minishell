/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:56:57 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/21 23:15:08 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
To review the freeing of grp->heredoc
*/
void	open_heredoc_child(t_shell *shell, t_cmdgroup *grp, t_token *token)
{
	char	*line;

	grp->heredoc = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, token->next->str) || line == NULL)
		{
			free(line);
			line = NULL;
			break ;
		}
		translateinheredoc(shell, &line);
		strjoinandfree(&(grp->heredoc), line);
		strjoinandfree(&(grp->heredoc), "\n");
		free(line);
		line = NULL;
	}
}
