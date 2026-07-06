/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 08:30:00 by boris            #+#    #+#             */
/*   Updated: 2026/05/07 08:30:00 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	run_ast(t_cmd *ast);

/*
@brief READ SHELL LINE
** Read one command line from the interactive prompt and store it in history.
@param void
@return char* Newly allocated input line, or NULL when EOF is received.
*/
char	*read_shell_line(void)
{
	char	*line;

	setup_signal(0);
	line = readline("\001\033[1;33m\002URSShell\001\033[0m\002 $> ");
	if (line)
		add_history(line);
	setup_signal(1);
	return (line);
}

/*
@brief EVAL COMMAND
** Tokenize, expand, parse AST, execute command tree, return status.
@param line Raw command line from the prompt.
@param last_exit Exit status of the previous command (used for expansions).
@return int Exit status produced by the executed command.
*/
static int	eval_command(char *line, int last_exit)
{
	char	**split;
	t_token	*tokens;
	t_cmd	*ast;

	split = split_shell(line);
	if (!split)
		return (last_exit);
	tokens = build_token_list(split);
	free_tab(split);
	if (!tokens)
		return (2);
	expand_all_tokens(tokens, last_exit);
	ast = parse(tokens);
	free_token_list(tokens);
	if (!ast)
		return (2);
	last_exit = run_ast(ast);
	free_cmd(ast);
	return (last_exit);
}

/*
@brief PROCESS LINE
** Handle special shortcuts or evaluate the line as a shell command.
@param line Raw command line from the prompt.
@param last_exit Exit status of the previous command.
@return int Updated exit status after processing the input line.
*/
static int	process_line(char *line, int last_exit)
{
	if (ft_strcmp(line, "comrade") == 0)
	{
		comrade();
		return (last_exit);
	}
	return (eval_command(line, last_exit));
}

/*
@brief RUN SHELL
** Execute the REPL loop until EOF, evaluating each non-empty input line.
@param void
@return int Exit status of the last executed command before leaving the loop.
*/
int	run_shell(void)
{
	char	*line;
	int		last_exit;

	last_exit = 0;
	while (1)
	{
		line = read_shell_line();
		if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		if (*line)
			last_exit = process_line(line, last_exit);
		free(line);
	}
	return (last_exit);
}

/*
@brief MAIN
** Initialize shell data, run interactive loop, release resources, return status.
@param argc Number of arguments passed to the program (unused).
@param argv Program arguments array (unused).
@param envp Environment variables provided by the system.
@return int Exit status returned by the shell loop.
*/
int	main(int argc, char **argv, char **envp)
{
	int	last_exit;

	(void)argc;
	(void)argv;
	if (init_shell_env(envp))
		return (ft_putendl_fd("minishell: Memory allocation failed", 2), 1);
	setup_signal(0);
	last_exit = run_shell();
	readline_cleanup();
	cleanup_shell_env();
	return (last_exit);
}
