/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvk_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:26:20 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/25 23:43:01 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_first_key_char(char c)
{
	if (ft_isalpha(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

int	check_next_key_char(char c)
{
	if (ft_isalnum(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

int	first_key_error(t_shell *shell, char *str)
{
	if (!check_first_key_char(str[0]))
	{
		if (ft_strchr("-", str[0]))
			printerror(shell, "Argument is not a valid identifier\n",
				UNEXPTOKEN);
		else
			printerror(shell, "Argument is not a valid identifier\n",
				SYNTAXERROR);
		return (1);
	}
	return (0);
}

/*
cvk stands for Check Valid Key
This function will check the first character of a string during exporting.
It will return 1 if the first character is either an alphabet or an underscore.
It will return 0 otherwise.
It will also check the subsequent characters to check for special characters.
If a special characters exists beyond the first character of the key, it will
return 0 and 1 otherwise.
*/
int	cvk(t_shell *shell, char *str, int option)
{
	int	i;

	i = 1;
	if (first_key_error(shell, str))
		return (0);
	while (str[i] != '\0' && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
		{
			shell->exportflag = 1;
			break ;
		}
		if (!check_next_key_char(str[i++]))
		{
			printerror(shell, "Argument is not a valid identifier\n",
				SYNTAXERROR);
			return (0);
		}
	}
	if (option == 1 && ft_strchr(str, '='))
	{
		printerror(shell, "Argument is not a valid identifier\n", SYNTAXERROR);
		return (0);
	}
	return (1);
}
