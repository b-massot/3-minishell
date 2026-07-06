/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:00:00 by boris            #+#    #+#             */
/*   Updated: 2026/05/06 10:00:00 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern void	run_cmd(t_cmd *cmd);

/*
@brief PIPE RIGHT
** Configure the right child of a pipeline by redirecting stdin to pipe read end.
@param p Pipe command containing right subcommand to execute.
@param p_fd Pipe file descriptors array [read_end, write_end].
@return void
*/
void	pipe_right(t_pipecmd *p, int *p_fd)
{
	dup2(p_fd[0], STDIN_FILENO);
	close(p_fd[1]);
	close(p_fd[0]);
	run_cmd(p->right);
}
