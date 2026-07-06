/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 19:29:04 by ajeanren          #+#    #+#             */
/*   Updated: 2026/05/05 10:02:06 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parse_exec_node(t_token **current);

/*
@brief PARSE PIPE
** Recursively builds a pipe node from the token list
** If a PIPE token is found after the left command, it consumes
** the token and parses the right side recursively, then links both
** sides into a pipe command node
@param current
** pointer to the current token pointer (advanced as tokens are consumed)
@return
** a t_cmd pipe node linking left and right, or just the left cmd if no pipe,
** NULL on allocation failure
*/
static t_cmd	*parse_pipe(t_token **current)
{
	t_cmd	*left;
	t_cmd	*right;

	left = parse_exec_node(current);
	if (!left)
		return (NULL);
	if (*current && (*current)->type == PIPE)
	{
		*current = (*current)->next;
		right = parse_pipe(current);
		if (!right)
		{
			free_cmd(left);
			return (NULL);
		}
		return (pipecmd(left, right));
	}
	return (left);
}

/*
@brief PARSE
** Entry point of the parser
** Initializes the current token pointer and launches the recursive
** pipe parsing, which handles the full command tree
@param tokens
** head of the token list to parse
@return
** root of the parsed command tree (t_cmd), NULL if parsing fails
*/

t_cmd	*parse(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	return (parse_pipe(&current));
}
