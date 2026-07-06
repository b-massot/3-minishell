/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 20:13:30 by ajeanren          #+#    #+#             */
/*   Updated: 2026/05/05 10:12:16 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*remove_quotes(char *s);
char	*expand_and_strip(char *s, char **env, int last_exit);

/*
@brief EXPAND TOKEN
** Expands variables and strips quotes from a single WORD token in place.
@param token The token whose value will be expanded and replaced.
@param last_exit Exit code of the last command, used for $? expansion.
@return void
*/
static void	expand_token(t_token *token, int last_exit)
{
	char	*expanded;

	if (!token || !token->value)
		return ;
	if (!get_shell_env(NULL))
		return ;
	expanded = expand_and_strip(token->value, get_shell_env(NULL),
			last_exit);
	free(token->value);
	token->value = expanded;
}

/*
@brief EXPAND ALL TOKENS
** Iterates over the token list and expands every WORD token in place.
** Operator tokens (PIPE, REDIR_*) are left untouched.
@param tokens
** head of the token list to process
@param env
** environment variables used for $VAR expansion
@param last_exit
** exit code of the last command, used for $? expansion
@return
** void
*/
void	expand_all_tokens(t_token *tokens, int last_exit)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == WORD)
			expand_token(current, last_exit);
		current = current->next;
	}
}

/*
@brief REMOVE QUOTES
** Copies s into a new string with all quote characters removed,
** respecting quote nesting (single inside double and vice versa).
@param s
** input string possibly containing quote characters
@return char*
** newly allocated unquoted string, NULL on allocation failure
*/
char	*remove_quotes(char *s)
{
	char	*result;
	int		i;
	int		j;
	int		in_squote;
	int		in_dquote;

	result = malloc(ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_squote = 0;
	in_dquote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (s[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else
			result[j++] = s[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
