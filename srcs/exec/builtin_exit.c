/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:00:00 by boris             #+#    #+#             */
/*   Updated: 2026/05/13 09:52:06 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
@brief IS NUMERIC
** Validate shell numeric argument format: spaces, optional sign, digits, spaces.
@param arg Argument to check.
@return int 1 if numeric, 0 otherwise.
*/
static int	is_numeric(const char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	i = 0;
	while (arg[i] && ft_strchr(" \t\n\r", arg[i]))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i] || arg[i] < '0' || arg[i] > '9')
		return (0);
	while (arg[i] >= '0' && arg[i] <= '9')
		i++;
	while (arg[i] && ft_strchr(" \t\n\r", arg[i]))
		i++;
	return (arg[i] == '\0');
}

/*
@brief EXIT CODE MOD 256
** Compute bash-compatible exit status modulo 256 from a numeric argument.
@param arg Numeric argument.
@return int Value in [0, 255].
*/
static int	exit_code_mod256(const char *arg)
{
	int	i;
	int	sign;
	int	code;

	i = 0;
	sign = 1;
	code = 0;
	while (arg[i] && ft_strchr(" \t\n\r", arg[i]))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i] == '-')
			sign = -1;
		i++;
	}
	while (arg[i] >= '0' && arg[i] <= '9')
	{
		code = ((code * 10) + (arg[i] - '0')) % 256;
		i++;
	}
	if (sign < 0 && code != 0)
		code = 256 - code;
	return (code);
}

/*
@brief EXEC EXIT
** Execute exit builtin with bash-like validation and return codes.
@param ecmd Exit command node.
@return int 1 only for "too many arguments", otherwise function exits process.
*/
int	exec_exit(t_execcmd *ecmd)
{
	if (!ecmd->argv[1])
		exit(0);
	if (!is_numeric(ecmd->argv[1]))
	{
		write(2, "exit: ", 6);
		write(2, ecmd->argv[1], ft_strlen(ecmd->argv[1]));
		write(2, ": numeric argument required\n", 28);
		exit(2);
	}
	if (ecmd->argv[2])
		return (ft_putendl_fd("exit: too many arguments", 2), 1);
	exit(exit_code_mod256(ecmd->argv[1]));
	return (0);
}
