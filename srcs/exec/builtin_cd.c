/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:00:00 by boris             #+#    #+#             */
/*   Updated: 2026/05/05 13:39:03 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
@brief GET CD TARGET
** Returns target directory: no arg (HOME), "-" (OLDPWD), or argv[1].
@param argv Command arguments.
@return char* Target directory path.
*/
static char	*get_cd_target(char **argv)
{
	if (!argv[1])
		return (get_env_value("HOME"));
	if (ft_strcmp(argv[1], "-") == 0)
		return (get_env_value("OLDPWD"));
	return (argv[1]);
}

/*
@brief PRINT CD ERROR
** Write cd error to stderr. Differentiate "Not a directory" vs "No such file".
@param target Path that failed.
@param err Errno value from chdir().
@return void
*/
static void	print_cd_error(char *target, int err)
{
	write(2, "minishell: cd: ", 15);
	write(2, target, ft_strlen(target));
	write(2, ": ", 2);
	if (err == ENOTDIR)
		write(2, "Not a directory\n", 16);
	else
		write(2, "No such file or directory\n", 26);
}

/*
@brief BUILTIN CD
** Change working directory and update PWD/OLDPWD environment variables.
@param argv Arguments (argv[0]="cd", argv[1]=target or "-").
@return int 0 on success, 1 on error or too many arguments.
*/
int	builtin_cd(char **argv)
{
	char	*target;
	char	cwd[4096];
	char	*old_pwd;
	int		err;

	target = get_cd_target(argv);
	if (!target)
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	if (argv[2])
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	if (chdir(target) != 0)
		return (err = errno, print_cd_error(target, err), 1);
	old_pwd = get_env_value("PWD");
	if (getcwd(cwd, sizeof(cwd)))
	{
		if (old_pwd)
			set_env_var("OLDPWD", old_pwd);
		set_env_var("PWD", cwd);
		if (argv[1] && (ft_strcmp(argv[1], "-") == 0))
			ft_putendl_fd(cwd, 1);
	}
	return (0);
}
