/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 19:50:54 by ajeanren          #+#    #+#             */
/*   Updated: 2026/04/01 09:49:35 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
@brief IS SPACE
** Check if character is space or tab (token delimiters).
@param c Character to test.
@return int 1 if space/tab, 0 otherwise.
*/
static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

/*
@brief IS OPERATOR
** Check if character is shell operator (|, <, >).
@param c Character to test.
@return int 1 if operator, 0 otherwise.
*/
static int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
@brief WORD LENGTH
** Calculate length of word, respecting quotes (ignore spaces/ops in quotes).
@param s Start of word.
@return int Number of chars in word.
*/
static int	word_len(const char *s)
{
	int	i;
	int	in_squote;
	int	in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (s[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (!in_squote && !in_dquote
			&& (is_space(s[i]) || is_operator(s[i])))
			break ;
		i++;
	}
	return (i);
}

/*
@brief EXTRACT TOKEN
** Extract next token (operator or word) from s, advance position *i.
@param s Full input string.
@param i Pointer to current position in s.
@return char* Newly allocated token string, NULL on allocation failure.
*/
char	*extract_token(const char *s, int *i)
{
	int		len;
	char	*tok;

	if (is_operator(s[*i]))
		len = op_len(&s[*i]);
	else
		len = word_len(&s[*i]);
	tok = ft_substr(s, *i, len);
	*i += len;
	return (tok);
}

/*
@brief SPLIT SHELL
** Split input line into tokens. Handle quotes and operators.
@param s Input line to split.
@return char** NULL-terminated token array or NULL on error.
*/
char	**split_shell(const char *s)
{
	char	**tokens;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tokens = malloc(sizeof(char *) * (count_tokens(s) + 1));
	if (!tokens)
		return (NULL);
	while (s[i])
	{
		while (is_space(s[i]))
			i++;
		if (!s[i])
			break ;
		tokens[j++] = extract_token(s, &i);
	}
	tokens[j] = NULL;
	return (tokens);
}
