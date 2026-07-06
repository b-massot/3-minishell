/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 19:58:09 by ajeanren          #+#    #+#             */
/*   Updated: 2026/04/01 09:43:37 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
@brief IS SPACE
** Check if character is space or tab.
@param c Character to check.
@return int 1 if space/tab, 0 otherwise.
*/
static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

/*
@brief IS OPERATOR
** Check if character is shell operator (|, <, >).
@param c Character to check.
@return int 1 if operator, 0 otherwise.
*/
static int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
@brief WORD LENGTH
** Calculate length of a word, respecting single and double quotes.
@param s String starting with word.
@return int Length of word.
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
@brief OPERATOR LENGTH
** Operators >> and << take 2 characters, all others (|, <, >, etc) take 1.
@param s Pointer to operator.
@return int 2 for >> and <<, 1 for others.
*/
int	op_len(const char *s)
{
	if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
		return (2);
	return (1);
}

/*
@brief COUNT TOKENS
** Count tokens in input line, ignoring spaces. Parse each word or operator.
@param s Input line to scan.
@return int Total number of tokens found.
*/
int	count_tokens(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (is_space(s[i]))
			i++;
		if (!s[i])
			break ;
		count++;
		if (is_operator(s[i]))
			i += op_len(&s[i]);
		else
			i += word_len(&s[i]);
	}
	return (count);
}
