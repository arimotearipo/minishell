#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include "libft.h"

/*
** EXIT STATUS
*/
# define SUCCESS 0
# define SYNTAXERROR 1
# define NOCOMMAND 127
# define NOEXECUTE 126

/*
** QUOTE TYPE
*/
# define DOLLARDEL -1
# define SQUOTE 39
# define DQUOTE 34

/*
** TOKEN TYPE
*/ 
# define COMMAND 1 // eg: echo, pwd, grep, awk, etc
# define ARG 2 // inputs after commands. eg: "hello world"
# define FD	3 // Any argument that is a file descriptor
# define INPUT 4 // < redirection to left. Grab input from fd on the right and pass as argument to left
# define OUTPUT 5 // > redirection to right. Redirect output from left to right which should be an fd
# define APPEND 6 // >> double redirection. Take output from left and append to fd on the right
# define RDINPUT 7 // << double redirection. Read input from user until EOF is met as pass as argument to programme on left
# define DELIM 8 // EOF which should come after <<
# define PIPE 9 // | Take output from left of pipe and pass as argument to command on right of pipe

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmdgroup
{
	t_token				*tokens;
	int					cmdcnt;
	// int				tkn_count;
	int					fdin;
	int					fdout;
	struct	s_cmdgroup  *next;
	char				*grpstr;
	char				*output;
	char				*topass;
}	t_cmdgroup;

typedef struct s_shell
{
	t_cmdgroup	*cmdgroup;
	char		**sh_env;
	int			cmdgrpcount;
	int			exit;
}	t_shell;

int			collecttoken(char *line, t_cmdgroup *cmd, int *i);
void		printerror(t_shell *shell, char *msg, int errortype);
void		emptycommand(t_shell *shell);
void		checkline(t_shell *shell);
void		redirectionislast(t_shell *shell);
void		filllst(t_cmdgroup *cmd, char *str, int i, int len);
int			addlist(t_cmdgroup *cmd, char *str, int i, int len); // Maybe to replace filllst
void		addnewlst(t_token *lst);
void		clearmemory(t_shell *shell, t_cmdgroup *lst);
void		showlist(t_cmdgroup *cmd);
void		creategroup(t_cmdgroup **cmdgroup, int count);
int			gettokenlen(char *line, int *i);
int			getredlen(char *line, char c, int *i);
int			getlen(char *line, int *i);
int			getquotedlen(char *line, char c, int *i, int *len);
void		parser(t_shell *shell);
void		free2d(char **arr);
void		clone_env(char **envp, t_shell *shell);
char		*ft_getenv(char **env, char *var);
void		expand(t_shell *shell);
char		*ft_substrnoquote(char const *s, unsigned int start, size_t len);

#endif