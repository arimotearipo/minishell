/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:56:57 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/22 13:42:26 by wwan-taj         ###   ########.fr       */
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

void	open_heredoc_parent(t_cmdgroup *grp)
{
	int		fd;
	int		readbytes;
	char	buf[PATH_MAX];

	fd = open(".ttiyut7", O_RDONLY);
	readbytes = read(fd, buf, PATH_MAX);
	buf[readbytes] = '\0';
	grp->heredoc = ft_strdup(buf);
	close(fd);
}

void	runallheredocs(t_shell *shell, t_cmdgroup *grp)
{
	t_cmdgroup	*first;
	t_token		*firsttoken;

	first = grp;
	while (grp != NULL)
	{
		firsttoken = grp->tokens;
		while (grp->tokens != NULL)
		{
			if (grp->tokens->type == RDINPUT)
			{
				shell->heredocflag = 1;
				open_heredoc(shell, grp, grp->tokens);
			}
			grp->tokens = grp->tokens->next;
		}
		grp->tokens = firsttoken;
		grp = grp->next;
	}
	grp = first;
}
