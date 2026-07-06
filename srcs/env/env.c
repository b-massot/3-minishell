/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 10:16:00 by boris            #+#    #+#             */
/*   Updated: 2026/05/05 10:16:00 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
@brief COPY ENV
** Create a deep copy of environment variables array.
@param envp Original environment array.
@return char** Allocated copy, NULL on failure.
*/
char	**copy_env(char **envp)
{
	char	**copy;
	int		i;

	i = 0;
	while (envp && envp[i])
		i++;
	copy = ft_calloc(i + 512, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp && envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

/*
@brief FREE ENV
** Free all allocated environment variable strings and array.
@param env Environment array to free.
@return void
*/
void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

/*
@brief GET SHELL ENV
** Get or set the shell environment copy (static storage).
@param env Environment to set (NULL to just get).
@return char** Pointer to shell environment copy.
*/
char	**get_shell_env(char **env)
{
	static char	**shell_env = NULL;

	if (env)
		shell_env = env;
	return (shell_env);
}

/*
@brief INIT SHELL ENV
** Initialize shell environment from system envp.
@param envp System environment array.
@return int 0 success, 1 error.
*/
int	init_shell_env(char **envp)
{
	char	**copy;

	copy = copy_env(envp);
	if (!copy)
		return (1);
	get_shell_env(copy);
	return (0);
}

/*
@brief CLEANUP SHELL ENV
** Free the shell environment copy.
@return void
*/
void	cleanup_shell_env(void)
{
	char	**env;

	env = get_shell_env(NULL);
	if (env)
		free_env(env);
}
