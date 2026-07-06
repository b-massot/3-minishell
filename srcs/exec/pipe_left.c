/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_left.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:00:00 by boris            #+#    #+#             */
/*   Updated: 2026/05/06 10:00:00 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

extern void	run_cmd(t_cmd *cmd);

/*
@brief PIPE LEFT
** Redirect stdout to pipe write end and run the left subcommand.
@param p Pipe command containing left subcommand to execute.
@param p_fd Pipe file descriptors array [read_end, write_end].
@return void
*/
void	pipe_left(t_pipecmd *p, int *p_fd)
{
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[0]);
	close(p_fd[1]);
	run_cmd(p->left);
}
