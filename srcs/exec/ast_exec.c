/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 08:30:00 by boris            #+#    #+#             */
/*   Updated: 2026/05/05 14:00:00 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Forward declarations */
int		wait_and_status(pid_t pid);
int		exec_builtin(t_execcmd *ecmd);
void	run_cmd(t_cmd *cmd);
void	setup_signal(int mode);

/*
@brief RUN AST
** Main AST execution orchestrator:
** 1. Try to execute builtin in parent (if EXEC command)
** 2. Fork child for other commands
** 3. Setup parent signal handlers
** 4. Wait for child and return normalized status.
@param ast Root AST command node.
@return int Exit code of executed command.
*/
int	run_ast(t_cmd *ast)
{
	pid_t	pid;
	int		ret;

	if (ast->type == EXEC)
	{
		ret = exec_builtin((t_execcmd *)ast);
		if (ret != -1)
			return (ret);
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		run_cmd(ast);
	}
	setup_signal(2);
	return (wait_and_status(pid));
}
