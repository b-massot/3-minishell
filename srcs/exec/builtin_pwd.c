/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:00:00 by boris             #+#    #+#             */
/*   Updated: 2026/05/05 13:38:54 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
@brief BUILTIN PWD
** Print PWD env var from g_env copy. Use PWD, not getcwd(), to respect symlinks.
@param void
@return int 0 always (success).
*/
int	builtin_pwd(void)
{
	char	*pwd;

	pwd = get_env_value("PWD");
	if (pwd)
		ft_putendl_fd(pwd, 1);
	return (0);
}
