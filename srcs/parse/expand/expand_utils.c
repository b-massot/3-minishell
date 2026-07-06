/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 20:14:39 by ajeanren          #+#    #+#             */
/*   Updated: 2026/03/24 16:58:14 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern char	*append_piece(char *result, char *piece);
extern char	*handle_dollar(char *s, int *i, char **env, int last_exit);

/*
@brief HANDLE QUOTE TOGGLE
** Handles opening/closing quotes in the expansion loop.
@param s input string
@param i pointer to position
@param quote pointer to quote state
@return char* empty string (for consistency)
*/
static char	*handle_quote(char *s, int *i, char *quote)
{
	if (!*quote && (s[*i] == '\'' || s[*i] == '"'))
	{
		*quote = s[(*i)++];
		return (ft_strdup(""));
	}
	if (*quote && s[*i] == *quote)
	{
		*quote = 0;
		(*i)++;
		return (ft_strdup(""));
	}
	return (NULL);
}

/*
@brief MAIN EXPANSION LOOP
** Processes all characters: handles quotes and $ expansions.
** Returns result or NULL on error.
@param s input string
@param result accumulated result string
@param env environment variables
@param last_exit exit code
@return char* result string, or NULL
*/
static char	*expand_loop(char *s, char **result, char **env, int last_exit)
{
	int		i;
	char	*piece;
	char	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		piece = handle_quote(s, &i, &quote);
		if (!piece)
		{
			if (s[i] == '$' && s[i + 1] && s[i + 1] != ' ' && quote != '\'')
				piece = handle_dollar(s, &i, env, last_exit);
			else
				piece = ft_substr(s, i++, 1);
		}
		*result = append_piece(*result, piece);
		if (!*result)
			return (NULL);
	}
	return (*result);
}

/*
@brief EXPAND AND STRIP
** Expands $VAR and $?, strips quotes.
@param s raw token string
@param env environment variables
@param last_exit exit code of last command
@return char* expanded and unquoted string, NULL on failure
*/
char	*expand_and_strip(char *s, char **env, int last_exit)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	return (expand_loop(s, &result, env, last_exit));
}
