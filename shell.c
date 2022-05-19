#include "minishell.h"

int	main(void)
{
	t_cmd	cmd;
	char 	*line;

	line = "echo hello world";

	counttoken(line, &cmd);
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

void	skipstr(char *line, char quote, int *count, int *i)
{
	(*i)++;
	while (line[*i] != quote && line[*i] != '\0')
		*i += 1;
	if (line[*i] == quote)
	{
		*count += 1;
		(*i)++;
	}
	else
		printerror();
}

// void	skipspace(char *line, char space, int *count, int *i)
// {
// 	(*i)++;
// 	while (line[*i] == space && line[*i] != '\0')
// 		(*i)++;
	
// }

int		counttoken(char	*line, t_cmd *cmd)
{
	int		count;
	int		i;
	int		space;
	int		len;

	count = 0;
	i = 0;
	space = 1;
	len = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"' || line[i] == '\'')
			skipstr(line, line[i], &count, &i);
		if (line[i] <= 32 && space == 0)
			space = 1;
		else if (line[i] > 32 && space == 1)
		{
			len = 0;
			while (line[len + i] > 32)
				len++;
			filllst(&(cmd->tokens), line, i, len);
			i += len - 1;
			space = 0;
			count++;
		}
		i++;
	}
	return (count);
}

// void	gettokens(char *line, t_cmd *cmd)
// {
// 	int	count;
// 	int	i;

// 	count = counttoken(line, cmd);
// 	cmd->tokens = malloc(sizeof(char *) * count + 1);
// 	cmd->tokens[count] = NULL;
// 	i = 0;
// 	while (cmd->tokens[i] != NULL)
// 	{
// 		i++;
// 	}
// }