/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:00:00 by boris             #+#    #+#             */
/*   Updated: 2026/04/01 09:43:41 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
@brief BUILTIN ECHO
** Print args separated by spaces. -n flag suppresses final newline.
@param argv Arguments array (argv[0]="echo").
@return void
*/
void	builtin_echo(char **argv)
{
	int	i;
	int	j;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n')
	{
		j = 2;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j])
			break ;
		n_flag = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
}
