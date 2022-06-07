/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:06:04 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/08 01:49:47 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int ac, char **av, char **envp)
// {
// 	t_shell		shell;
// 	char		*line;
// 	// char		*line = "$USER $NOTHING $ hello $'hello' "$USER" "$NOTHING" "$ USER" "$'USER'" '$USER' '$NOTHING' '$ USER' '$"USER'";
// 	// char		*line = "echo | >> e asd | << delim file.txt argument";
// 	// char	*line = "echo .. hello world \"test\" | asda >> <<  | cat -e < \"123 ' > << | >>";
// 	// line = ft_strdup("echo test > xx >");
// 	// line = ft_strdup("a<<b'''' '''''''''''c'\"d\" | echo 'a'b>c makan\"hello\"world'lagi'\"dan\"next | echo 'one'\"two\"three|four");
// 	// line = ft_strdup("\"$ USER\"");

// 	(void)av;
// 	if (ac != 1)
// 		return (1);
// 	shell.exit = 0;
// 	initshell(&shell, envp);
// 	while (1)
// 	{
// 		// clone_env(envp, &shell);
// 		shell.exit = 0;
// 		line = readline("minishell>% "); // Jangan lupa comment free(line)
// 		if (ft_strcchr(line, "exit", ' ') == 0)
// 			break ;
// 		if (ft_strcchr(line, "env", ' ') == 0)
// 			showenv(&shell);
// 		if (ft_strcchr(line, "export", ' ') == 0)
// 			export(&shell, "ZZZZZZZZZZZZZZZZZZZZZ=AKSDASDASDASDASDASDASDASDASD");
// 		add_history(line);
// 		lexer(line, &shell);
// 		parser(&shell);
// 		checkline(&shell);
// 		if (isnoterror(shell.exit))
// 			showlist(shell.cmdgroup);
// 		clearmemory(&shell, shell.cmdgroup);
// 		// break ;
// 	}
// 	clearmemory(&shell, shell.cmdgroup);
// 	free2d(shell.sh_env);
// 	// system("leaks minishell");
// 	return (0);
// }

int	main(int ac, char **av, char **envp)
{
	t_shell shell;

	(void)ac;
	(void)av;
	initshell(&shell, envp);
	// showenv(&shell);
	// printf("INIT----------------------------------\n");
	// export(&shell, "testing=555");
	// showenv(&shell);
	// printf("EXPORT----------------------------------\n");
	// unset(&shell, "testing");
	// showenv(&shell);
	// printf("UNSET TESTING----------------------------------\n");
	unset(&shell, "SHELL");
	showenv(&shell);
	printf("UNSET TERM----------------------------------\n");
	return (0);	
}