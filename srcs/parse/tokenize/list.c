/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 10:30:00 by boris             #+#    #+#             */
/*   Updated: 2026/04/01 09:43:39 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
@brief IS QUOTED
** Check if token has quotes. Return 2 for double, 1 for single, 0 otherwise.
@param str Token string.
@return int 2 if double-quoted, 1 if single-quoted, 0 otherwise.
*/
static int	is_quoted(char *str)
{
	int		i;
	char	open_quote;

	i = 0;
	open_quote = 0;
	while (str[i])
	{
		if (!open_quote && (str[i] == '\'' || str[i] == '"'))
		{
			open_quote = str[i];
			if (open_quote == '"')
				return (2);
			else
				return (1);
		}
		i++;
	}
	return (0);
}

/*
@brief WHICH TOKEN TYPE
** Identify token type: |, >>, >, <<, < or word. Return t_token_type.
@param token Raw token string.
@return t_token_type Token type (PIPE, REDIR_OUT, REDIR_IN, etc).
*/
static t_token_type	which_token_type(char *token)
{
	if (token[0] == '|')
		return (PIPE);
	if (token[0] == '>' && token[1] == '>')
		return (REDIR_APPEND);
	if (token[0] == '>')
		return (REDIR_OUT);
	if (token[0] == '<' && token[1] == '<')
		return (HEREDOC);
	if (token[0] == '<')
		return (REDIR_IN);
	return (WORD);
}

/*
@brief NEW TOKEN
** Allocate t_token and init: type, quoted flag, value (copy).
@param value Raw token string to store.
@return t_token* New token or NULL on error.
*/
static t_token	*new_token(char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->quoted = is_quoted(value);
	token->type = which_token_type(value);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	return (token);
}

/*
@brief BUILD TOKEN LIST
** Convert NULL-term array to linked list of t_token, validate syntax.
@param split Array of raw token strings from split_shell.
@return t_token* Head of list or NULL on error.
*/
t_token	*build_token_list(char **split)
{
	t_token	*head;
	t_token	*current;
	t_token	*new_tok;
	int		i;

	if (!split || !split[0])
		return (NULL);
	head = new_token(split[0]);
	if (!head)
		return (NULL);
	current = head;
	i = 1;
	while (split[i])
	{
		new_tok = new_token(split[i]);
		if (!new_tok)
			return (free_token_list(head), NULL);
		current->next = new_tok;
		current = new_tok;
		i++;
	}
	if (!check_syntax(head))
		return (free_token_list(head), NULL);
	return (head);
}
