/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:58:36 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/07 14:59:07 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c
			&& (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	words_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_free(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;

	str = malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!s || !str)
		return (0);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			str[j] = ft_substr(s, i, words_len(&s[i], c));
			if (!str[j])
				return (ft_free(str, j));
			j++;
			i += words_len(&s[i], c);
		}
		else
			i++;
	}
	str[j] = 0;
	return (str);
}
/*
#include <stdio.h>

int main(void)
{
	char **test;

	int i = 0;
	char s[] = "Hello comment ca va?";
	char c = ' ';
	test = ft_split(s, c);
	while (test[i])
	{
		printf("%s\n", test[i]);
		i++;
	}
	return (0);
}
*/