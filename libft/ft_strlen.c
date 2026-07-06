/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:00:48 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/07 15:00:50 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
#include <stdio.h>
int main(void)
{
	char test[] = "HHH";
	printf("%zu\n", ft_strlen(test));
	printf("%zu\n", sizeof(test));

	return (0);
}
*/
