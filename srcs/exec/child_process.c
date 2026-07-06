/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:00:00 by boris            #+#    #+#             */
/*   Updated: 2026/05/05 14:00:00 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
@brief WAIT AND STATUS
** Wait for child process and normalize exit status.
** Exit codes: 0-255 for WEXITSTATUS, 128+signal for WIFSIGNALED, 1 for error.
@param pid Child process ID to wait for.
@return int Normalized exit status code.
*/
int	wait_and_status(pid_t pid)
{
	int		status;

	while (waitpid(pid, &status, 0) < 0)
	{
		if (errno != EINTR)
			return (1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
