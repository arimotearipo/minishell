/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:06:04 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/26 20:57:54 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_of_file(t_shell *shell)
{
	free2d(shell->sh_env);
	exit(0);
}

void	lexer_and_parser(t_shell *shell, char *line)
{
	lexer(line, shell);
	parser(shell);
	checkline(shell);
	setlastcommand(shell);
}

void	reset_value_and_signal(t_shell *shell)
{
	g_sigint = 0;
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	shell->exit = 0;
}

void	launch_minishell(char **envp)
{
	t_shell	shell;
	char	*line;

	initshell(&shell, envp);
	while (42)
	{
		reset_value_and_signal(&shell);
		line = readline("cangkerang>% ");
		if (line == NULL)
			end_of_file(&shell);
		if (ft_strempty(line) == 0)
		{
			free(line);
			continue ;
		}
		sigint_set_exit_value(&shell, g_sigint);
		add_history(line);
		lexer_and_parser(&shell, line);
		if (isnoterror(shell.exit))
			execution(&shell, shell.cmdgroup);
		updateexitvalue(&shell);
		clearmemory(&shell, shell.cmdgroup);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
	{
		ft_putendl_fd("Anything not asked is not required.", 2);
		exit(NOCOMMAND);
	}
	banner();
	launch_minishell(envp);
	return (0);
}
