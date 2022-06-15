/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getallpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:57:34 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/06/09 17:42:52 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This getallpath() function might be redundant */
char	**getallpath(t_shell *shell)
{
	char	**binpath;
	char	*pwd;

	binpath = ft_split(ft_getenv(shell->sh_env, "PATH"), ':');
	pwd = ft_getenv(shell->sh_env, "PWD");
	ft_append2d(&binpath, pwd);
	return (binpath);
}
