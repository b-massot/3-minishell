/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:02:24 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/07 15:02:26 by bmassot          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

/*
#include <stdio.h>
int	main()
{
	int i = 0;
	char test[] = "Hello";
	while (i < sizeof(test) - 1)
	{
		printf("%c ", tolower(test[i]));
		i++;
	}
	return (0);
}
*/
