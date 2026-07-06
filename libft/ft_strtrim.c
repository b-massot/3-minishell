/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:01:57 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/07 15:01:59 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	len = ft_strlen(s1);
	while (start < len && ft_strchr(set, s1[start]))
		start++;
	if (start == len)
		return (ft_strdup(""));
	end = len - 1;
	while (end > start && ft_strrchr(set, s1[end]))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}
/*
OU

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int in_set(char c, const char *set)
{
    while (*set)
    {
        if (c == *set)
            return (1);
        set++;
    }
    return (0);
}

char *ft_strtrim(char *s, char *set)
{
    int start = 0;
    int end = strlen(s);
    int i = 0;
    char *new;

    while (s[start] && in_set(s[start], set))
        start++;
    while (end > start && in_set(s[end - 1], set))
        end--;

    new = malloc(end - start + 1);
    if (!new)
        return (NULL);

    while (start < end)
        new[i++] = s[start++];
    new[i] = '\0';

    return (new);
}

int main()
{
    char s[] = "aaHello commentaa";
    char set[] = "a";

    printf("%s\n", ft_strtrim(s, set));  // ➜ "Hello comment"
    return (0);
}




int	main()
{
	char test[] = "aaComment ca vaa";
	char set[] = "a";
	printf("%s\n", ft_strtrim(test, set));
	return (0);
}
*/
