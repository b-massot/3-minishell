/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:52:53 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/07 14:52:57 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	char	a = '1';
	char	b = 0x80;

	printf("isascii(a): %d\n", isascii(a));
	printf("ft_isascii(a): %d\n", ft_isascii(a));
	printf("isascii(b): %d\n", isascii(b));
	printf("ft_isascii(b): %d\n", ft_isascii(b));
}
*/
