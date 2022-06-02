/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:06:04 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/02 20:24:12 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell		shell;
	char		*line;
	// char		*line = "$USER $NOTHING $ hello $'hello' "$USER" "$NOTHING" "$ USER" "$'USER'" '$USER' '$NOTHING' '$ USER' '$"USER'";
	// char		*line = "echo | >> e asd | << delim file.txt argument";
	// char	*line = "echo .. hello world \"test\" | asda >> <<  | cat -e < \"123 ' > << | >>";
	// line = ft_strdup("echo test > xx >");
	// line = ft_strdup("a<<b'''' '''''''''''c'\"d\" | echo 'a'b>c makan\"hello\"world'lagi'\"dan\"next | echo 'one'\"two\"three|four");
	// line = ft_strdup("\"$ USER\"");

	(void)av;
	if (ac != 1)
		return (1);
	shell.exit = 0;
	while (1)
	{
		clone_env(envp, &shell);
		shell.exit = 0;
		line = readline("minishell>% "); // Jangan lupa comment free(line)
		if (ft_strcchr(line, "exit", ' ') == 0)
			exit(0);
		add_history(line);
		lexer(line, &shell);
		parser(&shell);
		checkline(&shell);
		if (isnoterror(shell.exit))
		{
			showlist(shell.cmdgroup);
			printf("\n\n\n\n");
			ft_echo(&shell, shell.cmdgroup);
		}
		clearmemory(&shell, shell.cmdgroup);
		// break ;
	}
	// system("leaks minishell");
	return (0);
}
