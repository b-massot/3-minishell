/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 08:00:00 by boris            #+#    #+#             */
/*   Updated: 2026/05/05 14:00:00 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
@brief PRINT ERROR
** Write formatted error message to stderr with minishell prefix.
** Format: "minishell: <cmd>: <msg>\n"
@param cmd Command name that caused error.
@param msg Error message description.
@return void
*/
void	print_error(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

/*
@brief HANDLE EXEC ERROR
** Decode errno from execve() failure and exit with appropriate code.
** Exit codes: 126 (permission/format), 127 (not found).
@param err Errno value from failed execve().
@param cmd Command name attempted to execute.
@param path Allocated path pointer (freed before exit).
@return void Never returns (calls exit()).
*/
void	handle_exec_error(int err, char *cmd, char *path)
{
	if (path)
		free(path);
	if (err == EISDIR)
		return (print_error(cmd, "Is a directory"), exit(126));
	if (err == EACCES)
		return (print_error(cmd, "Permission denied"), exit(126));
	if (err == ENOENT)
	{
		if (ft_strchr(cmd, '/'))
			print_error(cmd, "No such file or directory");
		else
			print_error(cmd, "command not found");
		exit(127);
	}
	perror(cmd);
	exit(126);
}

/*
@brief VALIDATE REDIRS
** Recursively validate all redirections in chain.
** Check: file not empty, can be opened with specified mode.
@param rcmd Redirection structure with file path and open mode.
@return int 0 on success, -1 on error (logs to stderr).
*/
int	validate_redirs(t_redircmd *rcmd)
{
	int	fd;

	if (rcmd->cmd->type == REDIR_IN || rcmd->cmd->type == REDIR_OUT
		|| rcmd->cmd->type == REDIR_APPEND || rcmd->cmd->type == HEREDOC)
		if (validate_redirs((t_redircmd *)rcmd->cmd) < 0)
			return (-1);
	if (rcmd->type == HEREDOC)
		return (0);
	if (!rcmd->file || !rcmd->file[0])
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", STDERR_FILENO);
		return (-1);
	}
	fd = open(rcmd->file, rcmd->mode, 0666);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(rcmd->file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (-1);
	}
	close(fd);
	return (0);
}
