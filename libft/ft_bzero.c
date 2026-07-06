/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:51:49 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/07 14:51:51 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *dest, size_t len)
{
	size_t			i;
	unsigned char	*dst;

	dst = (unsigned char *)dest;
	i = 0;
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
}

/*
#include <stdio.h>

int	main(void)
{
	char test[] = "Hello bro";
	ft_bzero(test, 5);
	write(1, test, sizeof(test) - 1);
	return (0);
}
*/
