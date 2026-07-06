/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:57:02 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/07 14:57:04 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	size_t				i;
	const unsigned char	*s;
	unsigned char		*d;

	if (!dest && !src)
		return (NULL);
	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	i = 0;
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <stdlib.h>

int     main(void)
{
    char src[] = "Yoop";
    // soit cela char dest[sizeof src];
    // soit un mallloc
    char *dest = malloc(sizeof(src) + 1);
    if (!dest)
        return (1);
    ft_memcpy(dest, src, 5);
    printf("%s ", dest);
    free(dest);
    return (0);
}
*/
