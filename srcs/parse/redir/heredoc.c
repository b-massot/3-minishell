/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:30:00 by boris             #+#    #+#             */
/*   Updated: 2026/05/13 09:40:21 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
@brief HEREDOC CHILD PROCESS
** Reads lines from stdin using readline, writes to pipe until delimiter.
@param fd Write-end file descriptor of the pipe for heredoc content
@param delim Delimiter string that stops the heredoc input (e.g., "EOF")
@return void (exits child process with 0 or 130)
*/
static void	heredoc_child_simple(int fd, const char *delim)
{
	char	*line;

	setup_signal(3);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			close(fd);
			exit(0);
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
	if (g_signal)
		exit(130);
	exit(0);
}

/*
@brief HEREDOC FORK CHILD
** Create a pipe then fork a child that reads heredoc lines into the pipe.
** The parent receives the read-end fd and the child's pid.
@param fd Two-element array filled with [read_end, write_end] of the pipe.
@param delim Delimiter string that ends heredoc input.
@return pid_t Child process id (parent path); does not return in child path.
*/
static pid_t	heredoc_fork_child(int *fd, const char *delim)
{
	pid_t	pid;

	if (pipe(fd) < 0)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		perror("fork");
		exit(1);
	}
	if (pid == 0)
		heredoc_child_simple(fd[1], delim);
	return (pid);
}

/*
@brief HEREDOC WAIT PARENT
** Close write-end, ignore signals, wait for heredoc child to finish.
** If child exits 130 (Ctrl+C), reset g_signal, close read-end, and exit 130.
** If child was killed by a signal, exit with 128 + signal number.
@param pid Child process id returned by heredoc_fork_child.
@param fd Pipe fd array; fd[1] is closed here, fd[0] kept for caller.
@return void (may exit if child was interrupted or signalled)
*/
static void	heredoc_wait_parent(pid_t pid, int *fd)
{
	int	status;

	close(fd[1]);
	setup_signal(1);
	waitpid(pid, &status, 0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		g_signal = 0;
		close(fd[0]);
		exit(130);
	}
	if (WIFSIGNALED(status))
	{
		close(fd[0]);
		exit(128 + WTERMSIG(status));
	}
}

/*
@brief EXECUTE HEREDOC REDIRECTION
** Forks child to read stdin until delimiter, parent waits and redirects pipe.
** Closes write-end, waits for child completion, restores signal handlers.
** If child exits 130 (Ctrl+C during input), propagates to parent and exits.
** Otherwise redirects stdin from pipe read-end and executes the command.
@param rcmd
** Redirection command structure containing file (delimiter) and cmd to execute
@return
** void (executes command or exits child)
*/
void	exec_heredoc(t_redircmd *rcmd)
{
	int		fd[2];
	pid_t	pid;

	pid = heredoc_fork_child(fd, rcmd->file);
	heredoc_wait_parent(pid, fd);
	if (dup2(fd[0], STDIN_FILENO) < 0)
	{
		close(fd[0]);
		perror("dup2");
		exit(1);
	}
	close(fd[0]);
	run_cmd(rcmd->cmd);
}
