#include "minishell.h"

int	main(void)
{
	t_cmd	cmd;
	char	*line;

	line = "    hello world       testa \"hah   aa\"   ";
	// line = "'hello world'";
	collecttoken(line, &cmd);
	while (cmd.tokens != NULL)
	{
		printf("%s\n", cmd.tokens->str);
		cmd.tokens = cmd.tokens->next;
	}
	// while (1)
	// {
	// 	line = readline("minishell% ");
	// 	counttoken(line, &cmd);
	// 	printf("%s\n", cmd.tokens->str);
	// 	add_history(line);
	// 	free(line);
	// }
	return (0);
}

int	gettokenlen(char *line, char c, int *i)
{
	int	len;

	len = 0;
	if (c == '\'' || c == '"')
	{
		(*i)++;
		len = 2;
	}
	while (line[*i] != c && line[*i] != '\0')
	{
		*i += 1;
		len++;
	}
	if (c == '\'' || c == '"')
	{
		if (line[*i] == '\'' || line[*i] == '"')
			(*i)++;
		else
		{
			printerror();
			return (-1);
		}
	}
	return (len);
}

void		collecttoken(char	*line, t_cmd *cmd)
{
	int		i;
	int		len;
	int		start;

	i = 0;
	start = 0;
	while (line[i] != '\0')
	{
		if (line[i] <= 32)
			i++;
		if (line[i] == '"' || line[i] == '\'')
		{
			start = i;
			len = gettokenlen(line, line[i], &i);
			filllst(&(cmd->tokens), line, start, len);
		}
		if (line[i] > 32 )
		{
			start = i;
			len = gettokenlen(line, ' ', &i);
			filllst(&(cmd->tokens), line, start, len);
		}
	}
}
