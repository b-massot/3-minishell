/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:22:15 by ajeanren          #+#    #+#             */
/*   Updated: 2026/05/07 08:38:51 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
@brief GET PATH
** Search for the PATH variable in the shell's environment.
** Skips the "PATH=" prefix and returns a pointer to the value only.
@param void
@return char*
** Pointer to the value part of the PATH entry (e.g. "/usr/bin:/bin"),
** or NULL if PATH is not set.
*/
char	*get_path(void)
{
	char	*path_entry;

	path_entry = get_env_var("PATH");
	if (path_entry)
		return (path_entry + 5);
	return (NULL);
}

/*
@brief FIND IN DIRS
** Search for an executable in a list of directories.
** Test each directory by building full path and checking
** if file exists and is executable (access X_OK).
@param dirs
** Array of directory paths to search
@param cmd
** Command name to find
@return char*
** Full allocated path or NULL if not found
*/
static char	*find_in_dirs(char **dirs, char *cmd)
{
	char	*tmp;
	char	*full;
	int		i;

	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		if (!tmp)
			return (free_tab(dirs), NULL);
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full)
			return (free_tab(dirs), NULL);
		if (access(full, X_OK) == 0)
			return (free_tab(dirs), full);
		free(full);
		i++;
	}
	return (free_tab(dirs), NULL);
}

/*
@brief GET CMD PATH
** Resolve the full path of a command.
** If command contains '/', return a copy as-is without checking existence.
** Otherwise, search PATH directories and return the first executable found.
@param cmd
** Command name (e.g. "ls") or path (e.g. "./script") to resolve.
@return char*
** Newly allocated path string, or NULL if not found in PATH.
** Note: paths containing '/' are returned without existence check.
*/
char	*get_cmd_path(char *cmd)
{
	char	*path_env;
	char	**dirs;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = get_path();
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	return (find_in_dirs(dirs, cmd));
}

/*
 L'EASTER EGG COMMUNISTE
** Affiche le manifesto depuis art/manifesto.txt avec des couleurs ANSI.
** Texte rouge pour l'en-tête et jaune pour le contenu avec petits délais.
** C'est une fonction de divertissement pour le shell.
@return void
*/
void	comrade(void)
{
	int		fd;
	char	c;

	fd = open("art/manifesto.txt", O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error opening file\n", 19);
		return ;
	}
	printf("\033[1;31m\n║  ☭  THE MANIFESTO  ☭  ║\n\n\033[0m");
	printf("\033[0;33m");
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\r')
			continue ;
		if (c == '\n')
			usleep(300);
		write(1, &c, 1);
	}
	printf("\033[0m\n");
	close(fd);
}
