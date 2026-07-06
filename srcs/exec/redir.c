/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 11:45:00 by boris            #+#    #+#             */
/*   Updated: 2026/05/05 14:00:00 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Forward declarations */
int		validate_redirs(t_redircmd *rcmd);
void	run_cmd(t_cmd *cmd);

/*
@brief SKIP DOMINATED REDIRS
** Skip nested redirections to same fd (only outermost applies).
@param rcmd Current redirection structure.
@return t_cmd* Command to execute (skipping dominated redirs).
*/
static t_cmd	*skip_dominated_redirs(t_redircmd *rcmd)
{
	t_cmd	*cmd;

	cmd = rcmd->cmd;
	while (cmd && (cmd->type == REDIR_IN || cmd->type == REDIR_OUT
			|| cmd->type == REDIR_APPEND || cmd->type == HEREDOC))
	{
		if (((t_redircmd *)cmd)->fd != rcmd->fd)
			break ;
		cmd = ((t_redircmd *)cmd)->cmd;
	}
	return (cmd);
}

/*
@brief EXEC REDIR
** Apply redirection with open/dup2, then execute nested command:
** 1. Validate all redirections in chain (files exist, permissions OK)
** 2. Open file with proper flags
** 3. Duplicate file descriptor to target FD
** 4. Skip dominated redirections (optimization)
** 5. Execute nested command in child (with redirection active).
@param rcmd Pointer to t_redircmd with file, mode, fd, and nested cmd.
@return void Returns only via exit() through run_cmd.
*/
void	exec_redir(t_redircmd *rcmd)
{
	int		fd;
	t_cmd	*cmd;

	if (validate_redirs(rcmd) < 0)
		exit(1);
	fd = open(rcmd->file, rcmd->mode, 0666);
	if (fd < 0)
		exit(1);
	if (dup2(fd, rcmd->fd) < 0)
	{
		close(fd);
		perror("dup2");
		exit(1);
	}
	close(fd);
	cmd = skip_dominated_redirs(rcmd);
	run_cmd(cmd);
}
