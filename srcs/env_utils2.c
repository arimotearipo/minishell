/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 00:17:43 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/06/27 17:25:19 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Returns a malloc string that contains the 'key' of the variable. The malloced
string is from the beginning until right before the '=' sign in the 2D shell
env array. The argument 'str' is a the complete key=value pair.
*/
char	*getvarname(char *str)
{
	int		i;
	char	*varname;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	varname = ft_substr(str, 0, i);
	return (varname);
}

// Will return the index of the variable in the sh_env specified by arg
// The string passed as arg should not include the '=' sign. Upon success,
// getvarindex() will return the index of the var and -1 upon failure.
int	getvarindex(t_shell *shell, char *arg)
{
	int	m;

	m = 0;
	while (shell->sh_env[m] != NULL)
	{
		if (!ft_strcchr(shell->sh_env[m], arg, '='))
			return (m);
		m++;
	}
	return (-1);
}

// Will check whether the arg argument passed is an already existing variable
// in the 2D shell environment. The string passed in arg is the full argument
// that includes the '=' sign and the value of the variable
// It will return the index of the var if it is
// found, it will return -1 if it is not found.
// This function may obsolete as getvarindex does almost the same thing.
int	getfullvarindex(t_shell *shell, char *arg)
{
	int		i;
	int		index;

	index = ft_strchri(arg, 0, '=');
	i = 0;
	while (shell->sh_env[i] != NULL)
	{
		if (!ft_strncmp(shell->sh_env[i], arg, index))
			return (i);
		i++;
	}
	return (-1);
}
