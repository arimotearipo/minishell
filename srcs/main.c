/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:06:04 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/20 21:38:32 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_of_file(t_shell *shell)
{
	free2d(shell->sh_env);
	exit(0);
}

void	launch_minishell(char **envp)
{
	t_shell	shell;
	char	*line;
	// char	*line = ft_strdup("echo hello");

	initshell(&shell, envp);
	while (42)
	{
		signal(SIGINT, &sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		shell.exit = 0;
		line = readline("minishell>% ");
		if (line == NULL)
			end_of_file(&shell);
		if (line[0] == '\0')
			continue ;
		add_history(line);
		lexer(line, &shell);
		parser(&shell);
		checkline(&shell);
		setlastcommand(&shell);
		if (isnoterror(shell.exit))
			runline(&shell, shell.cmdgroup);
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
