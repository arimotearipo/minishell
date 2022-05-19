#include "minishell.h"

void	filllst(t_token **lst, char *str, int	i, int len)
{
	t_token	*tokens;
	t_token	*last;

	last = *lst;
	tokens = malloc(sizeof(t_token));
	tokens->str = ft_substr(str, i, len);
	if (last == NULL)
	{
		*lst = tokens;
		return ;
	}		
	else
	{
		while (last->next)
			last = last->next; // Move current pointer to next list
		last->next = tokens;
	}
}