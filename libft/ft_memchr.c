/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:56:34 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/07 14:56:36 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t				i;
	const unsigned char	*s;

	i = 0;
	s = (const unsigned char *)str;
	while (i < n)
	{
		if (s[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}

/*memchr searches for the first occurrence of the character c (an unsigned
char) in the first n bytes of the string pointed to, by the argument s.

the code below is used to test the function*/

/*
#include <stdio.h>

int main () 
{
   const char str[] = "Comment ca va?";
   const char c1 = 'm';
   char *r;

   r = ft_memchr(str, c1, 20);

   printf("String search of %c is -> %s\n", c1, r);

   r = ft_memchr(str, c1, 2);

   printf("String search of %c is -> %s\n", c1, r);

   return(0);
}
*/
