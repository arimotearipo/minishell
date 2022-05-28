/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:28:06 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/25 13:57:53 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isbuiltin(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

int	iscommand(char *str)
{
	char			**binpath;
	DIR				*dir;
	struct dirent 	*entity;
	int				i;
	
	i = 0;
	binpath = ft_split(getenv("PATH"), ':');
	while (binpath[i] != NULL)
	{
		dir = opendir(binpath[i++]);
		entity = readdir(dir);
		while (entity != NULL)
		{
			if (ft_strcmp(str, entity->d_name) == 0)
			{	
				closedir(dir);
				free2d(binpath);
				return (1);
			}
			entity = readdir(dir);
		}
		closedir(dir);
	}
	free2d(binpath);
	return (0);
}

void	assigntype(t_token *token, int prevtype)
{
	if (prevtype == RDINPUT)
		token->type = DELIM;
	else if ((prevtype >= INPUT && prevtype <= APPEND)
				|| prevtype == DELIM)
		token->type = FD;
	else if (ft_strcmp(".", token->str) == 0 
				|| ft_strcmp("..", token->str) == 0)
		token->type = ARG;
	else if (iscommand(token->str) || isbuiltin(token->str))
		token->type = COMMAND;
	else if (ft_strcmp("<<", token->str) == 0)
		token->type = RDINPUT;
	else if (ft_strcmp("<", token->str) == 0)
		token->type = INPUT;
	else if (ft_strcmp(">", token->str) == 0)
		token->type = OUTPUT;
	else if (ft_strcmp(">>", token->str) == 0)
		token->type = APPEND;
	else if (ft_strcmp("|", token->str) == 0)
		token->type = PIPE;
	else
		token->type = ARG;
}

void	loopandassigntype(t_cmdgroup *cmd)
{
	t_token		*firsttoken;
	t_cmdgroup	*firstcmd;
	int			i;
	int			previoustype;

	firstcmd = cmd;
	i = 0;
	while (cmd != NULL)
	{
		previoustype = 0;
		firsttoken = cmd->tokens;
		while (cmd->tokens != NULL)
		{
			assigntype(cmd->tokens, previoustype);
			previoustype = cmd->tokens->type;
			cmd->tokens = cmd->tokens->next;
		}
		cmd->tokens = firsttoken;
		cmd = cmd->next;
		i++;
	}
	cmd = firstcmd;
}

// void	arrangetokens(t_cmdgroup *cmdgroup)
// {
	
// }

void	parser(t_shell *shell)
{
	loopandassigntype(shell->cmdgroup);
	/**
	 * Errorchecking: Need to make sure that first token of a command group is of type COMMAND or INPUT/OUTPUT/APPEND/RDINPUT
	 * Errorchecking: Need to check for empty command group.
	 * Errorchecking: Need to check for consecutive redirection (more than 2)
	 * Errorchecking: Need to deal with "<>" "< >" "><" "> <"" ">>>" "<<<"
	 * Echo needs to take in spaces
	 */
	// arrangetokens(shell->cmdgroup);
}