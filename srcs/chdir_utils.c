/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:16:37 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/22 15:16:44 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Might need to free home variable
char	*expandpath(char *arg)
{
	char	*home;
	char	*remainderpath;
	char	*fullpath;

	home = getenv("HOME");
	remainderpath = ft_substr(arg, 1, ft_strlen(arg));
	fullpath = ft_strjoin(home, remainderpath);
	free(remainderpath);
	return (fullpath);
}
