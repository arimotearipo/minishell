/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:21:25 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/05/29 17:11:51 by mahmad-j         ###   ########.fr       */
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

int	collecttoken(char *line, t_cmdgroup *cmd)
{
	int		i;
	int		len;
	int		start;

	i = 0;
	start = 0;
	while (line[i] != '\0')
	{
		start = i;
		if (line[i] <= 32)
		{
			i++;
			continue ;
		}
		if (line[i] == '|')
		{
			cmd = cmd->next;
			i++;
			continue ;
		}
		if (line[i] == '"' || line[i] == '\'')
			start++;
		len = getlen(line, &i);
		if (addlist(cmd, line, start, len) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	lexer(char *line, t_shell *shell)
{
	shell->cmdgrpcount = countcmdgroups(line);
	creategroup(&(shell->cmdgroup), shell->cmdgrpcount);
	collecttoken(line, shell->cmdgroup);
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
	// char	*line = "echo hello pwd test cat";
	
	(void)av;
	if (ac != 1)
		return (1);
	clone_env(envp, &shell);
	while (1)
	{
		line = readline("minishell>% "); // Jangan lupa comment free(line)
		if (ft_strncmp(line, "exit", 4) == 0)
			exit(0);
		add_history(line);
		lexer(line, &shell);
		parser(&shell);
		showlist(shell.cmdgroup);
		clearmemory(shell.cmdgroup);
		free(line);
		// break ;
	}
	// system("leaks minishell");
	return (0);
}