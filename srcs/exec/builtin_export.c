/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:00:00 by boris             #+#    #+#             */
/*   Updated: 2026/05/05 13:39:00 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
@brief PRINT ENV VAR
** Print one environment entry in bash "declare -x" format.
** Entries without '=' are printed name-only; others as NAME="value".
@param env_str String "NAME=value" or "NAME" from environment.
@return void
*/
static void	print_env_var(char *env_str)
{
	char	*equal;
	char	*name;
	int		name_len;

	equal = ft_strchr(env_str, '=');
	if (!equal)
	{
		ft_printf("declare -x %s\n", env_str);
		return ;
	}
	name_len = equal - env_str;
	name = ft_substr(env_str, 0, name_len);
	if (name)
	{
		ft_printf("declare -x %s=\"%s\"\n", name, equal + 1);
		free(name);
	}
}

/*
@brief SORT AND PRINT ENV
** Sort the environment array alphabetically and print each entry
** in "declare -x" format, skipping the "_" variable.
@param env Environment array (will be sorted in place).
@return void
*/
static void	sort_and_print_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env && env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		if (ft_strcmp(env[i], "_") != 0)
			print_env_var(env[i]);
		i++;
	}
}

/*
@brief EXPORT ONE VAR
** Export a single variable: empty string if no '=', or value after '='.
@param arg Argument "NAME[=value]".
@return void
*/
static void	export_one(char *arg)
{
	char	*equal;
	char	*key;

	equal = ft_strchr(arg, '=');
	if (!equal)
		set_env_var(arg, "");
	else
	{
		key = ft_substr(arg, 0, equal - arg);
		if (key)
		{
			set_env_var(key, equal + 1);
			free(key);
		}
	}
}

/*
@brief BUILTIN EXPORT
** With no arguments, print all exported variables in declare -x format.
** Otherwise validate and export each argument. All arguments are processed
** even if one is invalid; the return value reflects the last error seen.
@param argv Arguments (argv[0]="export", followed by NAME[=value] entries).
@return int 0 if all arguments are valid, 1 if any invalid identifier was found.
*/
int	builtin_export(char **argv)
{
	int	i;
	int	ret;

	if (!argv[1])
	{
		sort_and_print_env(get_shell_env(NULL));
		return (0);
	}
	ret = 0;
	i = 1;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			ret = 1;
		}
		else
			export_one(argv[i]);
		i++;
	}
	return (ret);
}
