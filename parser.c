#include "minishell.h"

int	identifytype(char *str, int isfirst)
{
	if (str[0] == '<' && str[1] == '<')
		return (RDINPUT);
	if (str[0] == '<')
		return (INPUT);
	if (str[0] == '>' && str[1] == '>')
		return (APPEND);
	if (str[0] == '>')
		return (OUTPUT);
	if (str[0] == '|')
		return (PIPE);
	if (iscommand == 1)
	{	
		cmd->cmdcount += 1;
		return (COMMAND);
	}
	else
		return (ARG);
}

int	iscommand(char *str)
{
	
}