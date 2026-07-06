/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:00:00 by boris             #+#    #+#             */
/*   Updated: 2026/05/05 13:39:01 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
@brief BUILTIN UNSET
** Remove variables from shell's env copy.
@param argv Arguments (argv[0]="unset").
@return int 0 always (success).
*/
int	builtin_unset(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		unset_env_var(argv[i]);
		i++;
	}
	return (0);
}
