/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:00:00 by boris            #+#    #+#             */
/*   Updated: 2026/05/05 14:00:00 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Forward declarations for all builtins */
void	builtin_echo(char **argv);
int		builtin_cd(char **argv);
int		builtin_pwd(void);
int		builtin_env(void);
int		builtin_export(char **argv);
int		builtin_unset(char **argv);
int		exec_exit(t_execcmd *ecmd);
int		builtin_hymne(void);
int		builtin_stop_hymne(void);

/*
@brief EXEC BUILTIN
** Route builtin command to appropriate handler.
** Supported builtins: echo, cd, pwd, env, export, unset, exit, hymne.
** Returns -1 if not a builtin (external command).
@param ecmd Command structure with argv array.
@return int Exit code of builtin, or -1 if not a builtin.
*/
int	exec_builtin(t_execcmd *ecmd)
{
	if (!ecmd || !ecmd->argv || !ecmd->argv[0] || !ecmd->argv[0][0])
		return (0);
	if (ft_strcmp(ecmd->argv[0], "echo") == 0)
		return (builtin_echo(ecmd->argv), 0);
	if (ft_strcmp(ecmd->argv[0], "cd") == 0)
		return (builtin_cd(ecmd->argv));
	if (ft_strcmp(ecmd->argv[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(ecmd->argv[0], "env") == 0)
		return (builtin_env());
	if (ft_strcmp(ecmd->argv[0], "export") == 0)
		return (builtin_export(ecmd->argv));
	if (ft_strcmp(ecmd->argv[0], "unset") == 0)
		return (builtin_unset(ecmd->argv));
	if (ft_strcmp(ecmd->argv[0], "exit") == 0)
		return (exec_exit(ecmd));
	if (ft_strcmp(ecmd->argv[0], "hymne") == 0)
		return (builtin_hymne());
	if (ft_strcmp(ecmd->argv[0], "hymne_stop") == 0)
		return (builtin_stop_hymne());
	return (-1);
}
