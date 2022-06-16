/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:07:40 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/16 20:42:40 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**argarr(t_shell *shell, t_token *token)
{
	t_token	*first;
	int		argcount;
	char	**argv;
	int		i;

	(void)shell;
	first = token;
	argcount = 0;
	while (token != NULL && (token->type == ARG || token->type == COMMAND))
	{
		argcount++;
		token = token->next;
	}
	argv = malloc(sizeof(char *) * argcount + 1);
	i = 0;
	token = first;
	while (i < argcount)
	{
		argv[i] = ft_strdup(token->str);
		token = token->next;
		i++;
	}
	token = first;
	argv[i] = NULL;
	return (argv);
}

char	*getcommandpath2(char **binpath, char *str, int i)
{
	char	*path;
	char	*path2;

	path2 = ft_strjoin("/", str);
	path = ft_strjoin(binpath[i - 1], path2);
	free(path2);
	return (path);
}

char	*getcommandpath(t_shell *shell, char *str, int i)
{
	char			**binpath;
	DIR				*dir;
	struct dirent	*entity;
	char			*path;

	binpath = ft_split(ft_getenv(shell->sh_env, "PATH"), ':');
	while (binpath[i] != NULL)
	{
		dir = opendir(binpath[i++]);
		entity = readdir(dir);
		while (entity != NULL)
		{
			if (ft_strcmp(str, entity->d_name) == 0)
			{	
				closedir(dir);
				path = getcommandpath2(binpath, str, i);
				free2d(binpath);
				return (path);
			}
			entity = readdir(dir);
		}
		closedir(dir);
	}
	free2d(binpath);
	return (NULL);
}

int	ft_execve(t_shell *shell, t_token *tkn, char *str)
{
	pid_t	pid;
	char	**args;
	char	*path;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		args = argarr(shell, tkn);
		path = getcommandpath(shell, tkn->str, 0);
		execve(str, args, shell->sh_env);
		if (path == NULL)
			printerror(shell, "Error. Command not found.\n", NOCOMMAND);
		execve(path, args, shell->sh_env);
		exit(shell->exit);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(-1, &status, 0);
	}
	shell->exit = status / 256;
	return (status);
}

void	run_program(t_shell *shell, t_cmdgroup *group)
{
	t_cmdgroup	*grp;

	grp = group;
	while (grp->tokens != NULL)
	{
		if (grp->tokens->type == COMMAND || grp->tokens->type == ARG)
		{
			exe_program(shell, grp->tokens, grp->tokens->str);
			break ;
		}
		grp->tokens = grp->tokens->next;
	}
}
