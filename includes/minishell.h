#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft.h"

# define COMMAND 1
# define ARG 2
# define INPUT 3
# define APPEND 4
# define PIPE 5
# define LASTARG 6

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd
{
	t_token			*tokens;
	// int				tkn_count;
	// struct	s_cmd 	*next;
}	t_cmd;

int		collecttoken(char *line, t_cmd *cmd);
void	printerror(t_cmd *cmd);
void	filllst(t_cmd *cmd, char *str, int i, int len);
int		addlist(t_cmd *cmd, char *str, int i, int len); // Maybe to replace filllst
void	addnewlst(t_token *lst);
void	clearmemory(t_cmd *cmd);
void	showlist(t_cmd *cmd);

#endif