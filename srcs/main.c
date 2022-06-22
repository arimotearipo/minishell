/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:06:04 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/22 15:21:13 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_of_file(t_shell *shell)
{
	free2d(shell->sh_env);
	system("leaks minishell");
	exit(0);
}

void	launch_minishell(char **envp)
{
	t_shell	shell;
	char	*line;

	initshell(&shell, envp);
	while (42)
	{
		g_sigint = 0;
		signal(SIGINT, &sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		shell.exit = 0;
		line = readline("minishell>% ");
		if (line == NULL)
			end_of_file(&shell);
		if (ft_strempty(line) == 0)
			continue ;
		if (g_sigint == 1)
		{
			updateexitvalue(&shell);
			g_sigint = 0;
		}
		add_history(line);
		lexer(line, &shell);
		parser(&shell);
		checkline(&shell);
		setlastcommand(&shell);
		if (isnoterror(shell.exit))
		{
			runallheredocs(&shell, shell.cmdgroup);
			runline(&shell, shell.cmdgroup);
		}
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
	launch_minishell(envp);
	return (0);
}
