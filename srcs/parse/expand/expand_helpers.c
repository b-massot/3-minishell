/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:50:00 by boris            #+#    #+#             */
/*   Updated: 2026/03/24 16:50:00 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
@brief GET VAR VALUE
** Looks up a variable name in the environment array and returns its value.
** Matches entries of the form "VAR=value" by comparing the name prefix.
@param env
** NULL-terminated environment array
@param var_name
** variable name to look up (without the '=')
@return char*
** pointer to the value inside env[i], NULL if not found
*/
char	*get_var_value(char **env, char *var_name)
{
	int	i;
	int	len;

	if (!env)
		return (NULL);
	len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

/*
@brief EXTRACT VAR NAME
** Reads an alphanumeric/underscore variable name from s starting at *i
** and advances *i past the name.
@param s
** input string containing the variable name
@param i
** pointer to the current position in s, updated on return
@return char*
** newly allocated string containing the variable name
*/
char	*extract_var_name(char *s, int *i)
{
	int		start;
	char	*var_name;

	start = *i;
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	var_name = ft_substr(s, start, *i - start);
	return (var_name);
}

/*
@brief HANDLE DOLLAR
** Processes a $ expansion at position *i in s.
** Handles $? (last exit code) and $VAR (environment lookup).
** Advances *i past the expanded token.
@param s
** input string
@param i
** pointer to current position (must point to '$')
@param env
** environment variables
@param last_exit
** exit code of the last command, substituted for $?
@return char*
** newly allocated expanded string, or "$" if not a valid expansion
*/
char	*handle_dollar(char *s, int *i, char **env, int last_exit)
{
	char	*var_name;
	char	*var_value;
	int		old_i;

	(*i)++;
	if (s[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(last_exit));
	}
	old_i = *i;
	var_name = extract_var_name(s, i);
	if (*i == old_i)
	{
		free(var_name);
		return (ft_strdup("$"));
	}
	var_value = get_var_value(env, var_name);
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	return (ft_strdup(var_value));
}

/*
@brief APPEND PIECE
** Concatenates piece into result, freeing both the old result and piece.
** Returns NULL and frees result if piece is NULL.
@param result
** current accumulated string
@param piece
** string to append, will be freed after join
@return char*
** newly joined string, NULL on failure or if piece is NULL
*/
char	*append_piece(char *result, char *piece)
{
	char	*tmp;

	if (!piece)
		return (free(result), NULL);
	tmp = result;
	result = ft_strjoin(result, piece);
	free(tmp);
	free(piece);
	return (result);
}
