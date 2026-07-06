/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_dispatch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 11:45:00 by boris            #+#    #+#             */
/*   Updated: 2026/05/05 14:00:00 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Forward declarations */
void	run_exec(t_execcmd *e);
void	exec_pipe(t_pipecmd *pcmd);
void	exec_heredoc(t_redircmd *rcmd);
void	exec_redir(t_redircmd *rcmd);

/*
@brief RUN CMD
** Dispatch AST command node to appropriate executor based on type.
** Types: EXEC (simple), PIPE (piped), REDIR_IN/OUT/APPEND (redirected), HEREDOC.
** All execution paths exit; this function never returns normally.
@param cmd Pointer to t_cmd AST node.
@return void Never returns (all paths call exit).
*/
void	run_cmd(t_cmd *cmd)
{
	if (!cmd)
		exit(0);
	if (cmd->type == EXEC)
		run_exec((t_execcmd *)cmd);
	else if (cmd->type == PIPE)
		exec_pipe((t_pipecmd *)cmd);
	else if (cmd->type == HEREDOC)
		exec_heredoc((t_redircmd *)cmd);
	else
		exec_redir((t_redircmd *)cmd);
	exit(0);
}
