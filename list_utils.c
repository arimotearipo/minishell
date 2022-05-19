#include "minishell.h"

void	filllst(t_token *lst, char *str, int	i, int len)
{
	addnewlst(lst);
	lst->token = ft_substr(str, i, len);
}

void	addnewlst(t_token *lst)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	lst->next = token;
	// lst->next->prev = lst;
	// lst->next->next = NULL;
	lst = lst->next;
}