/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:06:04 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/15 22:58:26 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	checkerror(int ac)
{
	if (ac != 1)
	{
		perror("No such file or directory\n");
		exit(NOCOMMAND);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell		shell;
	char		*line;

	(void)av;
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	checkerror(ac);
	initshell(&shell, envp);
	while (42)
	{
		shell.exit = 0;
		line = readline("minishell>% ");
		if (line == NULL)
			exit(0);
		add_history(line);
		lexer(line, &shell);
		parser(&shell);
		checkline(&shell);
		if (isnoterror(shell.exit))
			runline(&shell, shell.cmdgroup);
		updateexitvalue(&shell);
		clearmemory(&shell, shell.cmdgroup);
	}
	return (0);
}
