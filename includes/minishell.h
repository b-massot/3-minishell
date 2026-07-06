/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:21:54 by ajeanren          #+#    #+#             */
/*   Updated: 2026/05/05 13:47:58 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../libft/libft.h"

# define MAXARGS 128

extern volatile sig_atomic_t	g_signal;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	EXEC
}	t_token_type;

typedef enum e_error
{
	EMPTY_LINE,
	PIPE_SYNTAX,
	REDIR_SYNTAX,
}	t_error;

typedef struct s_cmd
{
	t_token_type	type;
}	t_cmd;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				quoted;
	struct s_token	*next;
}	t_token;

typedef struct s_execcmd
{
	t_token_type	type;
	char			**argv;
}	t_execcmd;

typedef struct s_pipecmd
{
	t_token_type	type;
	t_cmd			*left;
	t_cmd			*right;
}	t_pipecmd;

typedef struct s_redircmd
{
	t_token_type	type;
	t_cmd			*cmd;
	char			*file;
	int				mode;
	int				fd;
}	t_redircmd;

typedef struct s_redirarg
{
	char			*file;
	int				mode;
	int				fd;
	t_token_type	type;
}	t_redirarg;

// PARSING
t_cmd	*parse(t_token *tokens);
t_cmd	*exccmd(void);
t_cmd	*redircmd(t_cmd *subcmd, t_redirarg arg);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
int		check_syntax(t_token *head);

// EXEC
void	run_cmd(t_cmd *cmd);
char	*get_cmd_path(char *cmd);
void	exec_pipe(t_pipecmd *pcmd);
void	exec_redir(t_redircmd *rcmd);
void	exec_heredoc(t_redircmd *rcmd);
char	*get_path(void);

// BUILTINS
void	builtin_echo(char **argv);
int		exec_builtin(t_execcmd *ecmd);
int		exec_exit(t_execcmd *ecmd);

int		is_valid_identifier(const char *s);
int		builtin_cd(char **argv);
int		builtin_pwd(void);
int		builtin_env(void);
int		builtin_export(char **argv);
int		builtin_unset(char **argv);
int		builtin_hymne(void);
int		builtin_stop_hymne(void);
void	free_cmd(t_cmd *cmd);
void	free_tab(char **tab);
void	readline_cleanup(void);

// PARSING - LINKED LISTS
void	free_token_list(t_token *tokens);
t_token	*build_token_list(char **split);
char	**split_shell(const char *s);
char	*extract_token(const char *s, int *i);
int		count_tokens(const char *s);
int		op_len(const char *s);
void	expand_all_tokens(t_token *tokens, int last_exit);
void	setup_signal(int mode);
void	comrade(void);

// ENVIRONMENT MANAGEMENT
int		init_shell_env(char **envp);
void	cleanup_shell_env(void);
char	**get_shell_env(char **env);
char	*get_env_var(char *name);
char	*get_env_value(const char *name);
int		set_env_var(char *name, char *value);
void	unset_env_var(char *name);

// SHELL REPL
int		run_shell(void);
char	*read_shell_line(void);

#endif
