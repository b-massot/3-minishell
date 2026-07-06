/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:57:27 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/07 14:57:29 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)dest;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char str[30];
	strcpy(str, "Yoo comment ca va?");
	puts(str);
	ft_memset(str, 'A', 3);
	puts(str);
	return (0);
}
*/
