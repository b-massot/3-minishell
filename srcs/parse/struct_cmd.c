/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 19:37:42 by ajeanren          #+#    #+#             */
/*   Updated: 2026/04/01 09:50:38 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
@brief EXECCMD
** Allocate and initialize t_execcmd structure (simple command).
@param void
@return t_cmd* New EXEC structure or NULL on error.
*/
t_cmd	*exccmd(void)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	cmd->argv = malloc(sizeof(char *) * MAXARGS);
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	ft_memset(cmd->argv, 0, sizeof(char *) * MAXARGS);
	return ((t_cmd *)cmd);
}

/*
@brief REDIRCMD
** Allocate and init t_redircmd structure (file redirection).
@param subcmd Command to redirect.
@param arg Redirarg structure with file, mode, fd, type.
@return t_cmd* New REDIR structure or NULL on error.
*/
t_cmd	*redircmd(t_cmd *subcmd, t_redirarg arg)
{
	t_redircmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = arg.type;
	cmd->cmd = subcmd;
	cmd->file = ft_strdup(arg.file);
	if (!cmd->file)
	{
		free(cmd);
		return (NULL);
	}
	cmd->mode = arg.mode;
	cmd->fd = arg.fd;
	return ((t_cmd *)cmd);
}

/*
@brief PIPECMD
** Allocate and init t_pipecmd (connection of two commands).
@param left Left command of pipe.
@param right Right command of pipe.
@return t_cmd* New PIPE structure or NULL on error.
*/
t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}
