/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:07:40 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/13 22:59:22 by wwan-taj         ###   ########.fr       */
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
		args = argarr(shell, tkn);
		path = getcommandpath(shell, tkn->str, 0);
		execve(str, args, shell->sh_env);
		if (path == NULL)
			printerror(shell, "Error. Command not found.\n", NOCOMMAND);
		execve(path, args, shell->sh_env);
		exit(1);
	}
	else
		waitpid(0, &status, 0);
	shell->exit = status / 256;
	return (status);
}

void	exe_program(t_shell *shell, t_token *token, char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		exe_echo(shell, shell->cmdgroup, token);
	else if (ft_strcmp(str, "cd") == 0)
		exe_cd(shell, shell->cmdgroup);
	else if (ft_strcmp(str, "pwd") == 0)
		exe_pwd(shell, shell->cmdgroup);
	else if (ft_strcmp(str, "export") == 0)
		exe_export(shell, shell->cmdgroup, token);
	else if (ft_strcmp(str, "unset") == 0)
		exe_unset(shell, shell->cmdgroup, token);
	else if (ft_strcmp(str, "env") == 0)
		showenv(shell);
	else if (ft_strcmp(str, "exit") == 0)
		exe_exit(shell, shell->cmdgroup);
	else
		ft_execve(shell, token, str);
}

void	run_program(t_shell *shell, t_cmdgroup *group)
{
	t_cmdgroup	*grp;

	grp = group;
	while (grp->tokens != NULL)
	{
		if (grp->tokens->type == COMMAND || grp->tokens->type == ARG)
		{
			// printf("heree : %s\n", grp->tokens->str);
			exe_program(shell, grp->tokens, grp->tokens->str);
			break ;
		}
		grp->tokens = grp->tokens->next;
	}
}
