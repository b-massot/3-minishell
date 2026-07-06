/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:01:02 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/07 15:01:04 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;
	int				len;

	len = ft_strlen(s);
	i = 0;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (s[i])
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}

/*
#include <string.h>
#include <stdio.h>

char	tomaj(unsigned int i, char c)
{
	(void)i;
	if (c >= 'a' && c<= 'z')
			return (c -= 32);
	return (c);
}

int	main()
{
	char	s[] = "Testing this function";

	printf("%s\n",ft_strmapi(s, tomaj));

	return (0);
}
*/
