/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:21:25 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/01 21:34:28 by wwan-taj         ###   ########.fr       */
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
			// if (len > 2)
			// 	ft_putstr_fd("Unrecognized token\n", 2);
			// else
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

void	collect(char *line, int *i, t_cmdgroup *cmd, int *start)
{
	if (*i - *start > 0)
		addlist(cmd, line, *start, *i - *start);
	if (ft_strchr(" <>", line[*i]))
		skipseparator(cmd, line, i);
}

int	collecttoken(char *line, t_cmdgroup *cmd, int *i)
{
	int		openquote;
	char	quotetype;
	int		start;

	start = *i;
	openquote = 0;
	while (line[*i] != '\0')
	{
		assignquote(line, i, &quotetype, &openquote);
		if (line[*i] == '|' && openquote == 0)
		{
			collect(line, i, cmd, &start);
			(*i)++;
			return (1);
		}
		if (ft_strchr(" <>", line[*i]) && openquote == 0)
		{
			collect(line, i, cmd, &start);
			start = *i;
			continue ;
		}
		(*i)++;
	}
	collect(line, i, cmd, &start);
	return (0);
}

void	lexer(char *line, t_shell *shell)
{
	int			i;
	char		*temp;
	t_cmdgroup *first;

	i = 0;
	temp = line;
	line = ft_strtrim(line, " ");
	free(temp);
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
	// char		*line = "$USER $NOTHING $ hello $'hello' "$USER" "$NOTHING" "$ USER" "$'USER'" '$USER' '$NOTHING' '$ USER' '$"USER'";
	// char		*line = "echo | >> e asd | << delim file.txt argument";
	// char		*line = "'ab''cd' 'ef'";
	// char	*line = "echo .. hello world \"test\" | asda >> <<  | cat -e < \"123 ' > << | >>";
	// line = ft_strdup("a|b | c");
	// line = ft_strdup("\"$ USER\"");

	(void)av;
	if (ac != 1)
		return (1);
	while (1)
	{
		shell.exit = 0;
		clone_env(envp, &shell);
		line = readline("minishell>% "); // Jangan lupa comment free(line)
		if (ft_strncmp(line, "exit", 4) == 0)
			exit(0);
		add_history(line);
		lexer(line, &shell);
		parser(&shell);
		checkline(&shell);
		if (shell.exit != SYNTAXERROR)
			showlist(shell.cmdgroup);
		clearmemory(&shell, shell.cmdgroup);
		// free(line);
		// break ;
	}
	// system("leaks minishell");
	return (0);
}

// int	main(int ac, char **av)
// {
// 	char *str;
// 	int	res;

// 	(void)ac;
// 	str = ft_strdup("ABCDE=FGHIJK");
// 	res = ft_strcchr(str, av[1], av[2][0]);
// 	printf("str: %s\nres: %d\n", str, res);
// 	free(str);
// 	return (0);
// }