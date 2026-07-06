/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hymne.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 00:00:00 by                   #+#    #+#             */
/*   Updated: 2026/05/07 12:07:12 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
@brief BUILTIN HYMNE
** Play the Imperial March! 🚩
@param void
@return Always 0
*/
int	builtin_hymne(void)
{
	ft_putendl_fd("", STDOUT_FILENO);
	ft_putendl_fd("        🚩 IMPERIO, IMPERIO! 🚩", STDOUT_FILENO);
	ft_putendl_fd("", STDOUT_FILENO);
	system("ffplay -nodisp -autoexit art/imperial_march.wav 2>/dev/null &");
	return (0);
}

/*
@brief BUILTIN STOP HYMNE
** Stop playing the Imperial March
@param void
@return Always 0
*/
int	builtin_stop_hymne(void)
{
	system("pkill -f 'ffplay.*imperial_march' 2>/dev/null");
	ft_putendl_fd("🚩 Musique arrêtée.", STDOUT_FILENO);
	return (0);
}
