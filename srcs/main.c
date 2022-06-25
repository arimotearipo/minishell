/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:06:04 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/26 00:54:50 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_of_file(t_shell *shell)
{
	free2d(shell->sh_env);
	system("leaks minishell");
	exit(0);
}

void	sigint_set_exit_value(t_shell *shell, int sigint)
{
	if (sigint == 1)
	{
		updateexitvalue(shell);
		g_sigint = 0;
	}
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
			continue ;
		sigint_set_exit_value(&shell, g_sigint);
		add_history(line);
		lexer(line, &shell);
		parser(&shell);
		checkline(&shell);
		setlastcommand(&shell);
		if (isnoterror(shell.exit))
			execution(&shell, shell.cmdgroup);
		updateexitvalue(&shell);
		clearmemory(&shell, shell.cmdgroup);
	}
}

// int	main(int ac, char **av, char **envp)
// {
// 	(void)av;
// 	if (ac != 1)
// 	{
// 		ft_putendl_fd("Anything not asked is not required.", 2);
// 		exit(NOCOMMAND);
// 	}
// 	// banner();
// 	launch_minishell(envp);
// 	return (0);
// }

// For the purpose of using minishell tester
int	launch_minishell_for_tester(char **envp, char *line)
{
	t_shell	shell;

	line = ft_strdup(line);
	initshell(&shell, envp);
	lexer(line, &shell);
	parser(&shell);
	checkline(&shell);
	setlastcommand(&shell);
	if (isnoterror(shell.exit))
		execution(&shell, shell.cmdgroup);
	updateexitvalue(&shell);
	clearmemory(&shell, shell.cmdgroup);
	return (ft_atoi(ft_getenv(shell.sh_env, "?")));
}

int	main(int ac, char **av, char **envp)
{
	int	exit_status;

	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		exit_status = launch_minishell_for_tester(envp, av[2]);
		exit(exit_status);
	}
	else
		launch_minishell(envp);
	return (0);
}
