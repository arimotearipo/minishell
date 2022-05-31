/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:21:25 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/31 16:54:19 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isecho(char *str)
{
	while (*str <= 32)
		str++;
	if (ft_strcmp("echo", str) != 0)
		return (0);
	str += 4;
	if (*str <= 32)
		return (1);
	return (0);
}

int	countcmdgroups(char *line)
{
	int		count;
	int		openquote;
	char	quotetype;
	int		i;

	i = 0;
	openquote = 0;
	count = 1;
	while (line[i] != '\0')
	{
		if ((line[i] == '\'' || line[i] == '"') && openquote == 0)
		{
			openquote = 1;
			quotetype = line[i];
		}
		else if (line[i] == quotetype)
			openquote = 0;
		if (line[i] == '|' && openquote == 0)
			count++;
		i++;
	}
	return (count);
}

void	skipseparator(t_cmdgroup *cmd, char *line, int *i)
{
	char	redirection;
	int		len;
	int		start;
	
	while (ft_strchr("<> ", line[*i]) && line[*i])
	{
		if (ft_strchr("<>", line[*i]))
		{
			len = 0;
			start = *i;
			redirection = line[*i];
			while (line[*i] == redirection)
			{
				(*i)++;
				len++;
			}
			if (len > 2)
				ft_putstr_fd("Unrecognized token\n", 2);
			else
				addlist(cmd, line, start, len);
			continue ;
		}
		(*i)++;
	}
}

void	assignquote(char *line, int *i, char *quotetype, int *openquote)
{
	if ((line[*i] == '\'' || line[*i] == '\"') && *openquote == 0)
		{
			*openquote = 1;
			*quotetype = line[*i];
		}
		else if (line[*i] == *quotetype)
			*openquote = 0;
}

int	collecttoken(char *line, t_cmdgroup *cmd, int *i)
{
	int		openquote;
	char	quotetype;
	int		start;

	(void)cmd;
	start = *i;
	openquote = 0;
	while (line[*i] != '\0')
	{
		assignquote(line, i, &quotetype, &openquote);
		if (line[*i] == '|' && openquote == 0)
		{
			(*i)++;
			return (1);
		}
		if (ft_strchr(" <>", line[*i]) && openquote == 0)
		{
			if (*i - start > 0)
				addlist(cmd, line, start, *i - start);
			skipseparator(cmd, line, i);
			start = *i;
			continue ;
		}
		(*i)++;
	}
	addlist(cmd, line, start, *i - start);
	return (0);
}

char	*stripwhitespace(char *line)
{
	int		len;
	int		start;
	char	*newline;

	len = ft_strlen(line);
	start = 0;
	while (line[start] <= 32)
		start++;
	while (line[len] <= 32)
		len--;
	newline = ft_substr(line, start, len - start + 1);
	free(line);
	return (newline);
}

void	lexer(char *line, t_shell *shell)
{
	int			i;
	t_cmdgroup *first;

	i = 0;
	line = stripwhitespace(line);
	shell->cmdgrpcount = countcmdgroups(line);
	creategroup(&(shell->cmdgroup), shell->cmdgrpcount);
	first = shell->cmdgroup;
	while (collecttoken(line, shell->cmdgroup, &i) == 1)
		shell->cmdgroup = shell->cmdgroup->next;
	shell->cmdgroup = first;
}

int	main(int ac, char **av, char **envp)
{
	t_shell		shell;
	char		*line;
	// char		*line = "a<<b'''' '''''''''''c'\"d\" | echo 'a'b>c makan\"hello\"world'lagi'\"dan\"next | echo 'one'\"two\"three|four";
	// char		*line = "echo \"hello\"\"world\" | echo one\"hello\"'world'\"hi\"'name'\" next | echo \"hello\"   \"world\" ";
	// char		*line = "echo | >> e asd | << delim file.txt argument";
	// char		*line = "'ab''cd' 'ef'";
	// char	*line = "echo .. hello world \"test\" | asda >> <<  | cat -e < \"123 ' > << | >>";
	// char	*line = ft_strdup("echo | hello");
	
	(void)av;
	if (ac != 1)
		return (1);
	while (1)
	{
		clone_env(envp, &shell);
		line = readline("minishell>% "); // Jangan lupa comment free(line)
		if (ft_strncmp(line, "exit", 4) == 0)
			exit(0);
		add_history(line);
		lexer(line, &shell);
		parser(&shell);
		showlist(shell.cmdgroup);
		clearmemory(&shell, shell.cmdgroup);
		// free(line);
		// break ;
	}
	// system("leaks minishell");
	return (0);
}