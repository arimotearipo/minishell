/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:01:14 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/22 19:18:59 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <limits.h>
# include <sys/cdefs.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include "libft.h"

// BANNER DELAY
# define BANNERDELAY 40000000

// GET NEXT LINE
# define BUFFER_SIZE 20

/*
** FD VALUE
*/
# define STDIN 0
# define STDOUT 1
# define STDERR 2

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
** # define COMMAND 1 // eg: echo, pwd, grep, awk, etc
** # define INPUT 2 // < redirection to left
** # define OUTPUT 3 // > redirection to right
** # define APPEND 4 // >> double redirection
** # define RDINPUT 5 // << double redirection. Read input from user
** # define ARG 6 // inputs after commands. eg: "hello world"
** # define FD	7 // Any argument that is a file descriptor
** # define DELIM 8 // EOF which should come after <<
** # define PIPE 9 // | Pass output to next command group
*/
# define COMMAND 1
# define INPUT 2
# define OUTPUT 3
# define APPEND 4
# define RDINPUT 5
# define FD	6
# define DELIM 7
# define PIPE 8
# define ARG 9

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
	struct s_cmdgroup	*next;
	char				*grpstr;
	char				*output;
	char				*topass;
	char				*heredoc;
}	t_cmdgroup;

typedef struct s_shell
{
	char		*cmdline;
	t_cmdgroup	*cmdgroup;
	char		**sh_env;
	int			cmdgrpcount;
	int			exit;
	int			fdstdout;
	int			fdstdin;
	int			fdout;
	int			fdin;
	int			redirflag;
	int			eofexit;
	int			heredocflag;
	char		*lastcmd;
}	t_shell;

void		initshell(t_shell *shell, char **envp);
void		lexer(char *line, t_shell *shell);
int			collecttoken(char *line, t_cmdgroup *cmd, int *i);
void		printerror(t_shell *shell, char *msg, int errortype);
void		emptycommand(t_shell *shell);
void		checkfirsttoken(t_shell *shell);
void		checkline(t_shell *shell);
void		redirectionerror(t_shell *shell);
int			isnoterror(int errornum);
int			addlist(t_cmdgroup *cmd, char *str, int i, int len);
void		addnewlst(t_token *lst);
int			countcmdgroups(char *line);
void		clearmemory(t_shell *shell, t_cmdgroup *lst);
void		showlist(t_cmdgroup *cmd);
char		*getvarname(char *str);
int			getvarindex(t_shell *shell, char *arg);
int			searchdollarsign(char *str);
void		expandstr(char **new, char **str);
void		handledollar(char *cur, char next, int openquote, char quotetype);
void		markquote(char **var, int quote1, int quote2);
void		creategroup(t_cmdgroup **cmdgroup, int count);
int			gettokenlen(char *line, int *i);
int			getredlen(char *line, char c, int *i);
int			getlen(char *line, int *i);
int			getquotedlen(char *line, char c, int *i, int *len);
void		parser(t_shell *shell);
void		free2d(char **arr);
void		clone_env(char **envp, t_shell *shell);
char		*ft_getenv(char **env, char *var);
char		**getallpath(t_shell *shell);
void		expand(t_shell *shell);
char		*ft_substrnoquote(char *s, unsigned int start, size_t len);
int			getfullvarindex(t_shell *shell, char *arg);
void		replacevar(t_shell *shell, char *arg, int index);
void		insertvar(t_shell *shell, char *arg);
void		unset(t_shell *shell, char *arg);
void		updateexitvalue(t_shell *shell);
void		runline(t_shell *shell, t_cmdgroup *grp);
void		resetfd(t_shell *shell);
char		*get_next_line(int fd);
void		setlastcommand(t_shell *shell);
void		strjoinandfree(char **new, char *str);
int			cvk(t_shell *shell, char *str);
char		*expandpath(char *arg);
void		banner(void);

/*
**	SIGNAL HANDLER
*/
void		sigint_handler(int signum);

/*
** REDIRECTION FUNCTIONS
*/
void		runallheredocs(t_shell *shell, t_cmdgroup *grp);
void		open_heredoc(t_shell *shell, t_cmdgroup *grp, t_token *token);
void		open_heredoc_child(t_shell *shell, t_cmdgroup *grp, t_token *token);
void		open_heredoc_parent(t_cmdgroup *grp);
void		open_redirectionread(t_shell *shell, t_cmdgroup *grp, t_token *tkn);
void		open_redirectioninput(t_shell *shell, t_token *token);
void		open_redirectionright(t_shell *shell, t_token *token);
void		exe_redirection(t_shell *shell, t_cmdgroup *grp);
void		translateinheredoc(t_shell *shell, char **toexpand);

/*
** BUILT-IN FUNCTIONS
*/
int			cd(t_shell *shell, char *arg);
int			exe_echo(t_shell *shell, t_cmdgroup *cmd, t_token *token);
int			exe_pwd(t_shell *shell, t_cmdgroup *cmd);
int			exe_exit(t_shell *shell, t_cmdgroup *cmd);
void		exe_unset(t_shell *shell, t_cmdgroup *grp, t_token *token);
void		exe_export(t_shell *shell, t_cmdgroup *grp, t_token *token);
void		exe_cd(t_shell *shell, t_cmdgroup *grp);
void		showenv(t_shell *shell, t_token *token, int arg);

// EXECUTION
void		execution(t_shell *shell, t_cmdgroup *grp);
int			ft_execve(t_shell *shell, t_token *tkn, char *str);
void		exe_program(t_shell *shell, t_token *token, char *str);
void		run_program(t_shell *shell, t_cmdgroup *group);

int	g_sigint;

#endif