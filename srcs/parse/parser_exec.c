/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 19:41:47 by ajeanren          #+#    #+#             */
/*   Updated: 2026/04/01 10:19:43 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
@brief GET REDIR MODE
** Maps a redirection token type to its open() flags and target fd
@param type
** redirection token type (REDIR_IN, HEREDOC, REDIR_APPEND, REDIR_OUT)
@param mode
** output: open() flags to use
@param fd
** output: target file descriptor (STDIN or STDOUT)
@return
** void
*/
static void	get_redir_mode(t_token_type type, int *mode, int *fd)
{
	if (type == REDIR_IN || type == HEREDOC)
	{
		*mode = O_RDONLY;
		*fd = STDIN_FILENO;
	}
	else if (type == REDIR_APPEND)
	{
		*mode = O_WRONLY | O_CREAT | O_APPEND;
		*fd = STDOUT_FILENO;
	}
	else
	{
		*mode = O_WRONLY | O_CREAT | O_TRUNC;
		*fd = STDOUT_FILENO;
	}
}

/*
@brief PARSE REDIR
** Wraps a command node with a redirection node built from the current token
** Consumes the operator and filename tokens
@param subcmd
** the command to wrap with the redirection
@param current
** pointer to the current token pointer (the redirection operator)
@return
** a new redir cmd node wrapping subcmd, or subcmd unchanged if no filename
*/
static t_cmd	*parse_redir(t_cmd *subcmd, t_token **current)
{
	t_token		*op;
	t_redirarg	arg;
	int			mode;
	int			fd;

	op = *current;
	get_redir_mode(op->type, &mode, &fd);
	*current = op->next;
	if (!*current)
		return (subcmd);
	arg.file = (*current)->value;
	arg.mode = mode;
	arg.fd = fd;
	arg.type = op->type;
	subcmd = redircmd(subcmd, arg);
	*current = (*current)->next;
	return (subcmd);
}

/*
@brief ADD WORD TO ARGV
** Adds a word (quoted or unquoted) to argv. 
** Unquoted words with spaces are split on spaces; quoted are kept whole.
@param value word to add
@param argv argv array to fill
@param i pointer to current argv index
@return 0 on success, -1 on allocation failure
*/
static int	add_word_to_argv(const char *value, char **argv, int *i)
{
	char	**words;
	int		j;

	if (!value || !*value)
		return (0);
	words = ft_split(value, ' ');
	if (!words)
		return (-1);
	j = 0;
	while (words[j])
	{
		if (words[j][0] != '\0')
			argv[(*i)++] = ft_strdup(words[j]);
		j++;
	}
	free_tab(words);
	return (0);
}

/*
@brief HANDLE TOKEN
** Processes a single token: appends a WORD to argv or delegates to parse_redir
@param cmd current command node
@param ecmd exec subtype of cmd, used to fill argv
@param cur pointer to the current token pointer
@param i pointer to the current argv index
@return cmd on success, NULL on allocation failure
*/
static t_cmd	*handle_token(t_cmd *cmd,
		t_execcmd *ecmd, t_token **cur, int *i)
{
	if ((*cur)->type == WORD)
	{
		if (!(*cur)->quoted && (!(*cur)->value || (*cur)->value[0] == '\0'))
			return (*cur = (*cur)->next, cmd);
		if (!(*cur)->quoted)
		{
			if (add_word_to_argv((*cur)->value, ecmd->argv, i) < 0)
				return (free_cmd(cmd), NULL);
		}
		else
		{
			ecmd->argv[*i] = ft_strdup((*cur)->value);
			if (!ecmd->argv[*i])
				return (free_cmd(cmd), NULL);
			(*i)++;
		}
		*cur = (*cur)->next;
		return (cmd);
	}
	return (parse_redir(cmd, cur));
}

/*
@brief PARSE EXEC NODE
** Builds an exec command node by consuming WORD and redirection tokens
** until a PIPE or end of list is reached
@param current
** pointer to the current token pointer
@return
** a fully built t_execcmd node, NULL on allocation failure
*/
t_cmd	*parse_exec_node(t_token **current)
{
	t_cmd		*cmd;
	t_execcmd	*ecmd;
	int			i;

	cmd = exccmd();
	if (!cmd)
		return (NULL);
	ecmd = (t_execcmd *)cmd;
	i = 0;
	while (*current && (*current)->type != PIPE)
	{
		cmd = handle_token(cmd, ecmd, current, &i);
		if (!cmd)
			return (NULL);
	}
	ecmd->argv[i] = NULL;
	return (cmd);
}
