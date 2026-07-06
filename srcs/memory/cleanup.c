/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 20:29:50 by ajeanren          #+#    #+#             */
/*   Updated: 2026/05/05 10:02:06 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
@brief FREE TAB
** Frees a NULL-terminated array of strings and the array itself.
@param tab NULL-terminated string array to free.
@return void
*/
void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/*
@brief READLINE CLEANUP
** Clears the readline history and frees internal readline state.
@return void
*/
void	readline_cleanup(void)
{
	clear_history();
	rl_clear_history();
	rl_free_line_state();
}
