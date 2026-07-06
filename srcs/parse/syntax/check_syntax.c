/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 10:30:00 by boris             #+#    #+#             */
/*   Updated: 2026/03/24 14:47:03 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
@brief PRINT ERROR SYNTAX
** Prints a bash-style syntax error message to stderr for a missing
** or unexpected token. Uses "newline" if no valid token is found.
@param tok
** the problematic token, or NULL for an unexpected newline
@return
** void
*/
static void	print_error_syntax(t_token *tok)
{
	char	*prefix;
	char	*token_str;
	char	*suffix;

	prefix = "syntax error near unexpected token `";
	suffix = "'\n";
	if (tok && tok->type == REDIR_IN && tok->next)
		token_str = "<";
	else if (tok && tok->type == REDIR_OUT && tok->next)
		token_str = ">";
	else if (tok && tok->type == REDIR_APPEND && tok->next)
		token_str = ">>";
	else if (tok && tok->type == HEREDOC && tok->next)
		token_str = "<<";
	else if (tok && tok->type == PIPE)
		token_str = "|";
	else
		token_str = "newline";
	write(2, prefix, ft_strlen(prefix));
	write(2, token_str, ft_strlen(token_str));
	write(2, suffix, ft_strlen(suffix));
}

/*
@brief PRINT ERROR SYNTAX TOKEN
** Prints a bash-style syntax error message to stderr for a token
** that appears in an illegal position (e.g. consecutive operators).
** Unlike print_error_syntax, always uses the token's own value.
@param tok
** the unexpected token to report
@return
** void
*/
static void	print_error_syntax_token(t_token *tok)
{
	char	*prefix;
	char	*token_str;
	char	*suffix;

	prefix = "syntax error near unexpected token `";
	suffix = "'\n";
	if (tok->type == REDIR_IN)
		token_str = "<";
	else if (tok->type == REDIR_OUT)
		token_str = ">";
	else if (tok->type == REDIR_APPEND)
		token_str = ">>";
	else if (tok->type == HEREDOC)
		token_str = "<<";
	else if (tok->type == PIPE)
		token_str = "|";
	else
		token_str = "newline";
	write(2, prefix, ft_strlen(prefix));
	write(2, token_str, ft_strlen(token_str));
	write(2, suffix, ft_strlen(suffix));
}

/*
@brief IS REDIR TYPE
** Return 1 if the token type is any redirection operator, 0 otherwise.
@param type Token type to test.
@return int 1 if REDIR_IN, REDIR_OUT, REDIR_APPEND or HEREDOC; 0 otherwise.
*/
static int	is_redir_type(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == HEREDOC);
}

/*
@brief VALIDATE REDIR TOKEN
** Check that a redirection operator is followed by a WORD token.
** Prints a syntax error and returns 0 if followed by another operator or pipe.
@param current Token whose type is a redirection operator.
@return int 1 if the next token is a valid WORD target, 0 on syntax error.
*/
static int	validate_redir_token(t_token *current)
{
	if (is_redir_type(current->type) && current->next->type != WORD)
	{
		if (is_redir_type(current->next->type) || current->next->type == PIPE)
			return (print_error_syntax_token(current->next), 0);
		return (print_error_syntax(NULL), 0);
	}
	return (1);
}

/*
@brief CHECK SYNTAX
** Validates the token list against basic shell syntax rules:
** - list must not be empty or start with a PIPE
** - a PIPE must not be followed by another PIPE or end the list
** - a redirection operator must be followed by a WORD token
** Prints an error to stderr and returns 0 on the first violation.
@param head
** head of the token list to validate
@return int
** 1 if syntax is valid, 0 otherwise
*/
int	check_syntax(t_token *head)
{
	t_token	*current;

	if (!head)
		return (print_error_syntax(NULL), 0);
	if (head->type == PIPE)
		return (print_error_syntax(head), 0);
	current = head;
	while (current && current->next)
	{
		if (current->type == PIPE && current->next->type == PIPE)
			return (print_error_syntax_token(current->next), 0);
		if (!validate_redir_token(current))
			return (0);
		current = current->next;
	}
	if (current->type == PIPE)
		return (print_error_syntax(current), 0);
	if (current->type == REDIR_IN || current->type == REDIR_OUT
		|| current->type == REDIR_APPEND || current->type == HEREDOC)
		return (print_error_syntax(NULL), 0);
	return (1);
}
