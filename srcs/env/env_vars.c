/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 10:25:00 by boris            #+#    #+#             */
/*   Updated: 2026/05/05 10:25:00 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
@brief GET ENV VAR
** Find environment variable in shell's env copy.
@param name Variable name.
@return char* Pointer to "NAME=value" or NULL.
*/
char	*get_env_var(char *name)
{
	char	**env;
	int		i;
	int		len;

	env = get_shell_env(NULL);
	if (!env || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i]);
		i++;
	}
	return (NULL);
}

/*
@brief GET ENV VALUE
** Get environment variable value (without "NAME=" prefix).
@param name Variable name.
@return char* Pointer to value or NULL.
*/
char	*get_env_value(const char *name)
{
	char	*entry;
	int		len;

	entry = get_env_var((char *)name);
	if (!entry)
		return (NULL);
	len = ft_strlen(name);
	return (entry + len + 1);
}

/*
@brief UNSET ENV VAR
** Remove environment variable from shell's env copy.
@param name Variable name.
@return void
*/
void	unset_env_var(char *name)
{
	char	**env;
	int		i;
	int		len;

	env = get_shell_env(NULL);
	if (!env || !name)
		return ;
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			free(env[i]);
			while (env[i + 1])
			{
				env[i] = env[i + 1];
				i++;
			}
			env[i] = NULL;
			return ;
		}
		i++;
	}
}

/*
@brief FIND ENV POSITION
** Find position of env var or next available slot.
@param env Environment array.
@param name Variable name to find.
@return int Index position in env.
*/
static int	find_env_position(char **env, char *name)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (env[i] && (ft_strncmp(env[i], name, len) != 0 || env[i][len] != '='))
		i++;
	return (i);
}

/*
@brief SET ENV VAR
** Update or add environment variable in shell's env copy.
@param name Variable name.
@param value Variable value.
@return int 0 success, 1 error.
*/
int	set_env_var(char *name, char *value)
{
	char	**env;
	char	*tmp;
	char	*entry;
	int		i;

	if (!name)
		return (1);
	tmp = ft_strjoin(name, "=");
	entry = ft_strjoin(tmp, value);
	free(tmp);
	if (!entry)
		return (1);
	env = get_shell_env(NULL);
	if (!env)
		return (free(entry), 1);
	i = find_env_position(env, name);
	if (env[i] && env[i][0])
		free(env[i]);
	env[i] = entry;
	return (0);
}
