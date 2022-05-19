#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft.h"

typedef struct s_token
{
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	t_token			*tokens;
	int				tkn_count;
	struct s_cmd 	*next;
}	t_cmd;

// void	gettokens(char *line, t_cmd *cmd);
int		counttoken(char *line, t_cmd *cmd);
void	printerror(void);
void	filllst(t_token **lst, char *str, int	i, int len);
void	addnewlst(t_token *lst);

# endif