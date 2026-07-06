/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 11:45:00 by boris            #+#    #+#             */
/*   Updated: 2026/05/05 14:00:00 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Forward declarations */
void	print_error(char *cmd, char *msg);
void	handle_exec_error(int err, char *cmd, char *path);
char	*get_cmd_path(char *cmd);
int		exec_builtin(t_execcmd *e);
char	**get_shell_env(char **env);

/*
@brief RUN EXEC
** Execute a simple command (not pipe, not redir at this level):
** 1. Try builtin execution
** 2. Resolve command path via PATH environment variable
** 3. Execute via execve() with environment
** 4. Exit on errors (never returns on success).
@param e Pointer to t_execcmd structure with argv array.
@return void Never returns on success; exits on all paths.
*/
void	run_exec(t_execcmd *e)
{
	char		*path;
	char		**shell_env;
	int			ret;

	if (!e->argv[0])
		exit(0);
	ret = exec_builtin(e);
	if (ret != -1)
		exit(ret);
	path = get_cmd_path(e->argv[0]);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(e->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	shell_env = get_shell_env(NULL);
	execve(path, e->argv, shell_env);
	handle_exec_error(errno, e->argv[0], path);
}
