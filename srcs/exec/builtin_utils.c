/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:00:00 by boris             #+#    #+#             */
/*   Updated: 2026/05/05 16:06:39 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
@brief IS VALID IDENTIFIER
** Verify string is valid shell identifier for export validation.
@param s String to validate.
@return int 1 if valid, 0 otherwise.
*/
int	is_valid_identifier(const char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	if (!(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
