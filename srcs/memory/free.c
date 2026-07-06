/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 20:27:16 by ajeanren          #+#    #+#             */
/*   Updated: 2026/05/05 10:02:06 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd(struct s_cmd *cmd);

/*
@brief FREE EXEC
** Frees an exec command node: each argv string, the argv array, then the node
@param cmd
** exec command node to free
@return
** void
*/
static void	free_exec(struct s_execcmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
	{
		free(cmd->argv[i]);
		i++;
	}
	free(cmd->argv);
	free(cmd);
}

/*
@brief FREE REDIR
** Frees a redirection command node: recursively frees the wrapped command,
** the filename string, then the node itself
@param cmd
** redirection command node to free
@return
** void
*/
static void	free_redir(struct s_redircmd *cmd)
{
	free_cmd(cmd->cmd);
	free(cmd->file);
	free(cmd);
}

/*
@brief FREE PIPE
** Frees a pipe command node: recursively frees the left and right subtrees,
** then the node itself
@param cmd
** pipe command node to free
@return
** void
*/
static void	free_pipe(struct s_pipecmd *cmd)
{
	free_cmd(cmd->left);
	free_cmd(cmd->right);
	free(cmd);
}

/*
@brief FREE CMD
** Dispatches to the correct free function based on the command type.
** Safely handles NULL input
@param cmd
** command node to free (EXEC, PIPE or REDIR)
@return
** void
*/
void	free_cmd(struct s_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == EXEC)
		free_exec((struct s_execcmd *)cmd);
	else if (cmd->type == PIPE)
		free_pipe((struct s_pipecmd *)cmd);
	else
		free_redir((struct s_redircmd *)cmd);
}

/*
@brief FREE TOKEN LIST
** Iterates over the token linked list and frees each node and its value
@param tokens
** head of the token list to free
@return
** void
*/
void	free_token_list(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}
