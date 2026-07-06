/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:02:08 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/08 12:03:10 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static char	*ft_strjoin_free(char *s1, char *s2);
static char	*read_to_stash(int fd, char *stash);
static char	*extract_line(char *stash);
static char	*remove_line(char *stash);

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	if (s1)
		i = ft_strlen(s1);
	j = 0;
	if (s2)
		j = ft_strlen(s2);
	res = (char *)malloc(i + j + 1);
	if (!res)
		return (free(s1), NULL);
	j = 0;
	while (s1 && s1[j])
	{
		res[j] = s1[j];
		j++;
	}
	i = 0;
	while (s2 && s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	return (free(s1), res);
}

static char	*read_to_stash(int fd, char *stash)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	r;

	r = 1;
	while (r > 0 && (!stash || !ft_strchr(stash, '\n')))
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r < 0)
		{
			free(stash);
			return (NULL);
		}
		buf[r] = '\0';
		stash = ft_strjoin_free(stash, buf);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

static char	*extract_line(char *stash)
{
	size_t	i;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return (ft_substr(stash, 0, i));
}

static char	*remove_line(char *stash)
{
	size_t	i;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;
	new_stash = ft_substr(stash, i, ft_strlen(stash + i));
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = remove_line(stash);
	return (line);
}
