/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:00:00 by boris            #+#    #+#             */
/*   Updated: 2026/05/06 10:00:00 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>
#include <sys/wait.h>

extern void	run_cmd(t_cmd *cmd);
extern void	pipe_left(t_pipecmd *p, int *p_fd);
extern void	pipe_right(t_pipecmd *p, int *p_fd);

/*
@brief WAIT ONE CHILD
** Wait for one child process and retry if interrupted by a signal.
@param pid Child process id to wait for.
@param status Pointer to status storage, or NULL if status is not needed.
@return void
*/
static void	wait_one_child(pid_t pid, int *status)
{
	while (waitpid(pid, status, 0) < 0)
	{
		if (errno != EINTR)
			exit(1);
	}
}

/*
@brief EXEC PIPE
** Create a pipe, fork left and right children, close both pipe ends in parent,
** wait for both children, and exit with the right child's exit status.
@param pcmd Pipe command node containing left and right subcommands.
@return void (always exits — runs inside a child process)
*/
void	exec_pipe(t_pipecmd *pcmd)
{
	int		p_fd[2];
	pid_t	pid_l;
	pid_t	pid_r;
	int		status;

	if (pipe(p_fd) < 0)
		exit(1);
	pid_l = fork();
	if (pid_l == 0)
		pipe_left(pcmd, p_fd);
	pid_r = fork();
	if (pid_r == 0)
		pipe_right(pcmd, p_fd);
	close(p_fd[0]);
	close(p_fd[1]);
	wait_one_child(pid_l, NULL);
	wait_one_child(pid_r, &status);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		exit(128 + WTERMSIG(status));
	exit(1);
}
