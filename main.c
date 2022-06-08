/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:06:04 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/08 22:05:29 by wwan-taj         ###   ########.fr       */
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
	// line = ft_strdup("echo as'''");

	(void)av;
	if (ac != 1)
		return (1);
	shell.exit = 0;
	initshell(&shell, envp);
	while (1)
	{
		// clone_env(envp, &shell);
		shell.exit = 0;
		line = readline("minishell>% "); // Jangan lupa comment free(line)
		add_history(line);
		lexer(line, &shell);
		parser(&shell);
		checkline(&shell);
		if (isnoterror(shell.exit))
		{
			showlist(shell.cmdgroup);
			exe_builtin(&shell);
		}
		updateexitvalue(&shell);
		clearmemory(&shell, shell.cmdgroup);
		// break ;
	}
	clearmemory(&shell, shell.cmdgroup);
	free2d(shell.sh_env);
	// system("leaks minishell");
	return (0);
}


// main() function that is used to test the export and unset built-in functions
// int	main(int ac, char **av, char **envp)
// {
// 	t_shell shell;

// 	(void)ac;
// 	(void)av;
// 	initshell(&shell, envp);
// 	showenv(&shell);
// 	printf("INIT----------------------------------\n");
// 	export(&shell, "testing=555");
// 	showenv(&shell);
// 	printf("EXPORT----------------------------------\n");
// 	export(&shell, "additionalvar=aksjdhakhsd");
// 	showenv(&shell);
// 	printf("EXPORT----------------------------------\n");
// 	// unset(&shell, "testing");
// 	// showenv(&shell);
// 	// printf("UNSET TESTING----------------------------------\n");
// 	unset(&shell, "nothing");
// 	showenv(&shell);
// 	printf("UNSET nothing----------------------------------\n");
// 	return (0);	
// }

// main() function that is used to test the cd built-in function
// int	main(int ac, char **av, char **ep)
// {
// 	t_shell	shell;
// 	char	*path;

// 	(void)ac;
// 	(void)av;
// 	path = NULL;
// 	initshell(&shell, ep);
// 	showenv(&shell);
// 	printf("-----INIT-----\n");
// 	cd(&shell, path);
// 	showenv(&shell);
// 	printf("-----CD-----\n");
// 	return (0);
// }

// int	main(int ac, char **av, char **envp)
// {
// 	char	**arr;

// 	(void)ac;
// 	(void)av;
// 	arr = malloc(sizeof(char *) * 3);
// 	arr[0] = ft_strdup("cat");
// 	arr[1] = ft_strdup("error.c");
// 	arr[2] = NULL;
// 	execve("/bin/cat", arr, envp);
// 	return (0);
// }