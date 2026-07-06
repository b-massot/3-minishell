/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:00:00 by boris             #+#    #+#             */
/*   Updated: 2026/05/05 13:38:57 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
@brief BUILTIN ENV
** Print all env vars with values from shell's env copy.
@param void
@return int 0 always (success).
*/
int	builtin_env(void)
{
	char	**env;
	int		i;

	env = get_shell_env(NULL);
	i = 0;
	while (env && env[i])
	{
		if (ft_strchr(env[i], '='))
			ft_putendl_fd(env[i], 1);
		i++;
	}
	return (0);
}
