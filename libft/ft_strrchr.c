/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:01:43 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/07 15:01:45 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	ptr = (char *)s;
	i = 0;
	while (ptr[i])
		i++;
	if (ptr[i] == '\0' && (unsigned char) c == '\0')
		return (ptr + i);
	while (i--)
	{
		if (ptr[i] == (unsigned char) c)
			return (ptr + i);
	}
	ptr = NULL;
	return (ptr);
}
/*
OU

	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == char(c))
			return ((char *)(s + i));
		i--;
	}
	return (NULL);


*/
/*
#include <stdio.h>
int main ()
{
	const char	p[20] = "Hello comment-ca va";

	printf("%s\n", ft_strrchr(p, '-'));
	printf("%s\n", p);
}
*/
